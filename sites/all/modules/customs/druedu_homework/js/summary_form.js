(function ($) {
Drupal.behaviors.HomeworkFieldsetSummaries = {
  attach: function (context) {
    $('fieldset.classes_students', context).drupalSetSummary(function (context) {
      return Drupal.t('No Student selected');
    });
  }
};

})(jQuery);
