(function ($) {
Drupal.myWysiwygControl = {
  attach : attachWysiwyg,
  detach : detachWysiwyg
}

function detachWysiwyg(field) {
  var wysiwygField = null;
  if (wysiwygField = getWysiwygData(field)) {
    // Detach editor.
    Drupal.wysiwygDetach(wysiwygField.context, wysiwygField.params);
  }
  // Hide toggle link if visible.
  $('#wysiwyg-toggle-' + field).hide();
  // Hide the whole field and format selector.
  //$('#' + field).parents('.text-format-wrapper').hide();
}

function attachWysiwyg(field) {
  var wysiwygField = null;
  if ((wysiwygField = getWysiwygData(field))) {
    //(Re-)attach editor.
    Drupal.wysiwygAttach(wysiwygField.context, wysiwygField.params);
  }
  // Unhide the toggle link. (Also done by Drupal.wysiwygAttach, but it might not have run.)
  $('#wysiwyg-toggle-' + field).show();
  // Unhide the whole field and format selector.
  //$('#' + field).parents('.text-format-wrapper').show();
}

function getWysiwygData(field) {
  if (!Drupal.wysiwyg) {
    return false;
  }
  // Get any instance active for the field.
  var instance = Drupal.wysiwyg.instances[field];
  // Exit if no editor or it is disabled.
  // instance.trigger may be undefined when instance.editor == 'none'.
  if (!instance || instance.editor == 'none') {
    return false;
  }
  // Get per-format parameters for the field.
  var params = Drupal.settings.wysiwyg.triggers[instance.trigger];
  // Set the context to a parent element that wraps as much as possible of the
  // elements related to the field and format without overlapping other fields.
  var context = $('#' + field).parents('.text-format-wrapper');
  return {
    'instance' : instance,
    'params' : params[instance.format],
    'context' : context
  };
}

})(jQuery);
