// Mock Drupal objects used by Views Photo Grid.
Drupal = {};
Drupal.behaviors = {};
Drupal.settings = {};
Drupal.settings.viewsPhotoGrid = {gridSize: 'small', gridPadding: 3};

$(function () {

  // Renders the grid with random images.
  function renderImages() {
    Drupal.settings.viewsPhotoGrid.gridSize = $('.buttons-option-size').find('.active').attr('data-value');
    Drupal.settings.viewsPhotoGrid.gridPadding = $('.buttons-option-padding').find('.active').attr('data-value');
    var baseSize = (Drupal.settings.viewsPhotoGrid.gridSize == 'small' ? 150 : 500);
    var count = (Drupal.settings.viewsPhotoGrid.gridSize == 'small' ? 30 : 15);

    // Clear content.
    $('.views-photo-grid-container').empty();

    // Generate random-sized images.
    for (var i = 0; i < count; i++) {
      var w = baseSize + 50 * Math.round(5 * Math.random());
      var h = baseSize + 50 * Math.round(5 * Math.random());
      var url = 'http://lorempixel.com/' + w + '/' + h + '/';

      $('.views-photo-grid-container').append('<div class="views-photo-grid-item"><img src="' + url + '"></div>');
    }

    // Initialize Views Photo Grid.
    Drupal.behaviors.viewsPhotoGrid.attach();
  }

  // Click handler for the buttons.
  $('.buttons-option button').click(function () {
    $(this).parent().find('button').removeClass('active');
    $(this).addClass('active');

    renderImages();
  });

  renderImages();
});
