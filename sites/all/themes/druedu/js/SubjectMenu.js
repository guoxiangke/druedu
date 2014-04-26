function CreateSubjectMenu() {

  //Hide The JSON doc
  $('.view-subject-menu .view-content').hide();

  //Copy the JSON Doc
  var menuObject = jQuery.parseJSON( $('.view-subject-menu .view-content').html() );

  //Remove the JSON from the doc
  //$('.view-subject-menu .view-content').html('');

  var $menu = $('<ul>');

  function buildPageLevel(){}

  function buildUnitLevel(){}

  function buildSubjectLevel(){

    var Subjects = new Array();

    for (node in menuObject.nodes){
      console.log(node.Nid);
    }
  }

  buildSubjectLevel();
  return $menu.html();

}