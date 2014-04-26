jQuery(function($){
  // Add button (add select users form selection to right form)
  $('#edit-add').click(function(e) {
     e.preventDefault();
     ChangeAdmin('#edit-potential-administrators','#edit-administrators');
     if($('#edit-potential-members')){ 
     	ChangeAdmin('#edit-potential-members','#edit-class-members');
     }
  });
  
  $('#edit-remove').click(function(e) {
     e.preventDefault();
     ChangeAdmin('#edit-administrators','#edit-potential-administrators');
     if($('#edit-potential-members')){ 
     	ChangeAdmin('#edit-class-members','#edit-potential-members');
     }
  });
  /*
   * search select to add. 
   * */
  $("#edit-select").click(function(e){
  	 e.preventDefault();
  	 userName = $("#edit-search").val();
  	 //remove form potential
  	 //add to right admin or memeber
     //appendTo right form admins
     	//which option is the value:name?
     	value = false;
	  	$("#edit-potential-administrators option").each(function(){
	  		if($(this).html() == userName) {
	  			value = $(this).val();
	  			$(this).remove();
	  			TargetID = "#edit-administrators";
	  			return false;
	  		}
	  	});
	  	
     if((!value) && $('#edit-potential-members')){
        $("#edit-potential-members option").each(function(){
			 		if($(this).html() == userName) {
		  			value = $(this).val();
		  			$(this).remove();
		  			TargetID = "#edit-class-members";
		  			return false;
		  		}
			  });
      }
      
      if(value){
      	$('<option value="'+ value +'">'+ userName +'</option>').appendTo($(TargetID));
      	   //Op == add to post
			 if(TargetID == '#edit-administrators'){
				 oldPostAdmins =  $('#edit-posts-admins').val();
				 if(oldPostAdmins) {
				 	oldPostAdmins = oldPostAdmins +','+value;
				 }else{
				 	oldPostAdmins = value;
				 }
				 $('#edit-posts-admins').val(oldPostAdmins);	
			 }
			if(TargetID == '#edit-class-members'){
				 oldPostMembers =  $('#edit-posts-members').val();
				 if(oldPostMembers) {
				 	newPostMembers = oldPostMembers +','+value;
				 }else{
				 	newPostMembers = value;
				 }
				 $('#edit-posts-members').val(newPostMembers);
			 }
      }
  	 //clean the search 
  	 $("#edit-search").val('');
  });
/**
 * Function which returns the result of the subtraction method applied to
 * sets (mathematical concept).
 *
 * @param a Array one
 * @param b Array two
 * @return An array containing the result
 */
function diffArray(a, b) {
  var seen = [], diff = [];
  for ( var i = 0; i < b.length; i++)
      seen[b[i]] = true;
  for ( var i = 0; i < a.length; i++)
      if (!seen[a[i]])
          diff.push(a[i]);
  return diff;
}
function cleanArray(actual){
  var newArray = new Array();
  for(var i = 0; i<actual.length; i++){
      if (actual[i]){
        newArray.push(actual[i]);
    }
  }
  return newArray;
}
//FromID :the select ID
//TargetID :the target select ID.
     function ChangeAdmin(FromID,TargetID)//edit-potential-administrators
       {
         var SelUserVal =  '';
         var x = 0;
         var select = $(FromID);
					var oldPostAdmins = '';
					var oldPostAdmins = '';
					var oldPostMembers = '';
					var newPostMembers = '';
	       	$(FromID+' option:selected').each(function(){
	           //SelUserVal = SelUserVal + "," + $(this).attr('value') + ':' + $(this).html();
	           //SelUserVal[$(this).attr('value')] = $(this).html();
	           //remove item(option) form left form
	           $(this).remove();
	           //appendTo right form admins
	           $('<option value="'+ $(this).attr('value') +'">'+ $(this).html() +'</option>').appendTo($(TargetID));//'#edit-administrators'
						 //Op == add
						 if(FromID == '#edit-potential-administrators'){
							 oldPostAdmins =  $('#edit-posts-admins').val();
							 if(oldPostAdmins){
							 	oldPostAdmins = oldPostAdmins +','+ $(this).attr('value');
							 }else{
							 	oldPostAdmins = $(this).attr('value');
							 }
							 $('#edit-posts-admins').val(oldPostAdmins);	
						 }
						if(FromID == '#edit-potential-members'){
						 	
							 oldPostMembers =  $('#edit-posts-members').val();
							 if(oldPostMembers){
							 	newPostMembers = oldPostMembers +','+ $(this).attr('value')
							 }else{
							 	newPostMembers = $(this).attr('value')
							 }
							 $('#edit-posts-members').val(newPostMembers);
						 }
						 //Op == remove
						 if(FromID == '#edit-administrators'){
						   var oldPostAdminsArray = new Array();
							 oldPostAdminsArray =  $('#edit-posts-admins').val().split(",");
							  newArray = [$(this).attr('value')];
							  $new = diffArray(oldPostAdminsArray,newArray); //a-b
							 $('#edit-posts-admins').val($new.toString());
						 }
						if(FromID == '#edit-class-members'){
							 oldPostMembersArray =  $('#edit-posts-members').val().split(",");
							 newPostMembersArray = [$(this).attr('value')];
							 newArray = [$(this).attr('value')];
							 $new = diffArray(oldPostMembersArray,newArray); //a-b
							 $('#edit-posts-members').val($new.toString());
						 }
	       	});
     }  

    //when submit ,select All [left form,lost of potential to detimain which added] options of the selector
	  $('.form-submit[value="Submit"]').click(function(e){
	  	e.preventDefault();
	  	//unselect all .
	  	$("#edit-administrators option:selected").each(function(){ $(this).attr('selected',''); });
      if($('#edit-class-members option:selected')){
        $("#edit-potential-members option:selected").each(function(){ $(this).attr('selected',''); });
      }
      //left
	  	$("#edit-potential-administrators option:selected").each(function(){ $(this).attr('selected',''); });
      if($('#edit-potential-members option')){
        $("#edit-potential-members option:selected").each(function(){ $(this).attr('selected',''); console.log('21');});
      }
	    if($("#druedu-user-user-admin-form")) {
	    	$("#druedu-user-user-admin-form").submit();
	    }
	    if($("#druedu-public-admin-form")) {
	    	$("#druedu-public-admin-form").submit();
	    }
	  });
	
  $('#op-warning').hide();
  $('.op-warning').click(function(){
  	if($('#op-warning').html() == 'Operate Message'){
  		$('#op-warning').html('* Changes made in this table will not be saved until the form is submitted by clicking on "Confirm settings".').show();
  	}
  });

  // select change show notice.

  $('#druedu-user-user-filter-form select').change(function(){
  	if($(this).parents('.fieldset-wrapper').find('.warning').length == 0) {
  		$(this).parents('.fieldset-wrapper').prepend('<div id="op-notice" class="messages warning" style="display: block; ">* Please click \'Filter\' to see your changes, and if the filter button is not here: Please click \'Refine\' to see your changes.</div>');
  	}
  });
  $('#druedu-user-public-filter-form select').change(function(){
  	if($(this).parents('.fieldset-wrapper').find('.warning').length == 0) {
  		$(this).parents('.fieldset-wrapper').prepend('<div id="op-notice" class="messages warning" style="display: block; ">* Please click \'Filter\' to see your changes, and if the filter button is not here: Please click \'Refine\' to see your changes.</div>');
  	}
  });
  

  
});