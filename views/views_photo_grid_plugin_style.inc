<?php
/**
 * @file
 * Style plugin for Views Photo Grid.
 */

class views_photo_grid_plugin_style extends views_plugin_style {

  /**
   * Sets option defaults.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['grid_padding'] = array('default' => 1);

    return $options;
  }

  /**
   * Renders the options form.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['grid_padding'] = array(
      '#type' => 'textfield',
      '#title' => t('Padding'),
      '#size' => 2,
      '#description' => t('The amount of padding in pixels in between grid items.'),
      '#default_value' => $this->options['grid_padding'],
      '#maxlength' => 2,
    );
  }

  /**
   * Returns the name of the image field used in the view.
   */
  function get_image_field_name() {
    $fields = $this->display->handler->get_handlers('field');

    // Find the first non-excluded image field.
    foreach ($fields as $key => $field) {
      if (empty($field->options['exclude']) && !empty($field->field_info['type']) && $field->field_info['type'] == 'image') {
        return $key;
      }
    }

    return FALSE;
  }

  /**
   * Validates the view configuration.
   * Fails if there is a non-image field, or there are more
   * than one image fields that are not excluded from display.
   */
  function validate() {
    $errors = parent::validate();

    if (!is_numeric($this->view->vid)) {
      // Skip validation when the view is being created.
      // (the default field is a title field, which would fail.)
      return $errors;
    }

    // Get a list of fields that have been added to the display.
    $fields = $this->display->handler->get_handlers('field');

    // Check if there is exactly one image field to display.
    $fields_valid = TRUE;
    $field_count = 0;

    foreach ($fields as $key => $field) {
      // Ignore fields excluded from display.
      if (!empty($field->options['exclude'])) {
        continue;
      }

      if (empty($field->field_info['type']) || $field->field_info['type'] != 'image') {
        // Cannot display non-image fields. That would break the image grid.
        $fields_valid = FALSE;
        break;
      }

      $field_count++;
    }

    if (!$fields_valid || $field_count > 1) {
      $errors[] = t('This format can display only one image field and no other fields.');
    }

    return $errors;
  }

}
