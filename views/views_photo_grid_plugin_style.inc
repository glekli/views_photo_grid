<?php
/**
 * @file
 * Style plugin for Views Photo Grid.
 */

class views_photo_grid_plugin_style extends views_plugin_style {

  function get_image_field_name() {
    $fields = $this->display->handler->get_handlers('field');

    // Find the first non-excluded image field.
    foreach ($fields as $key => $field) {
      if (empty($field->options['exclude']) && $field->field_info['type'] == 'image') {
        return $key;
      }
    }

    return FALSE;
  }

  function validate() {
    $errors = parent::validate();

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

      if ($field->field_info['type'] != 'image') {
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
