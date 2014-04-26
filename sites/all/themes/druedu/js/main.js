var ua = navigator.userAgent;
var clickEvent = (ua.match(/iPad/i)) ? "touchstart" : "click";
$(function() {
	$('.toggle-subjects').click(function(e) {
		e.preventDefault();
		$('.subjects,.books').toggle(); // placeholder
	});
	$('.toggle-more-subjects').click(function(e) {
		e.preventDefault();
		$('.books .inner li.collapsible.collapsed').toggle(); // placeholder
	});

	$('.toggle-nav').click(function(e) {
		e.preventDefault();
		$('#sidebar-left .nav').toggle(); // placeholder
	});

	// Height of separators and sidebar
	$('.seperator, #sidebar-right, #workspace').css({'min-height':($('#content').innerHeight())+'px'});

	$(window).resize(function(){
	    resizeSeparator();
	});

	// Collapse accordions - Open the first one
	if(!$(".view-bulletins .accordion-body.in").length) {
		$(".view-bulletins .accordion-body").first().addClass('in');
	}

	$(".collapse").on('shown', function() {
		$('.seperator, #sidebar-right, #workspace').css({'min-height':($('#content').innerHeight())+'px'});
	});

    $('.collapse').on('hidden', function () {
  		$('.seperator, #sidebar-right, #workspace').css({'min-height':($('#content').innerHeight())+'px'});
    })

    $('#content').resize(function() {
  	$('.seperator, #sidebar-right, #workspace').css({'min-height': ($('#content').innerHeight())+'px'});
 	});	


	// Separator show/hide
	$('#hide-nav').click(function() {
	    hideSidebarLeft();
	    mainContentfullscreen();
	    resizeSeparator();
	});

	// While editing or adding, lets fade the left sidebar so we can focus on our content
	if ($('body').hasClass('page-node-edit', 'page-node-add')) {
		$('#daily-bulletin').hide();
		$('#sidebar-left').fadeTo(0,.5);
		$('#sidebar-left').hover(function() {
			$('#sidebar-left').fadeTo(0, 1);
		}, function() {
			$('#sidebar-left').fadeTo(500,.5);
		});
	};

	$('#hide-sidebar').click(function() {
	    hideSidebarRight();
	    mainContentfullscreen();
	    resizeSeparator();
	});

	function resizeSeparator(){
		$('.seperator, #workspace').css({'min-height':($('#content').innerHeight())+'px'});
	}

	function mainContentfullscreen() {
		if ($("#sidebar-left:visible").length) {
			$('#hide-nav').attr('style', '');
			if($("#sidebar-right:visible").length) {
		  		$('#main-content').attr('class','span7');
		  	}
		  	else {
		  		$('#main-content').attr('class','span10');
		  	}
		} 
		else {
		  	if($("#sidebar-right:visible").length) {
		  		$('#main-content').attr('class','span9');
		  	}
		  	else {
		  		$('#main-content').attr('class','span12');
		  	}
		}
	}

	function hideSidebarLeft() {
		$('#sidebar-left').animate({
	        width: 'toggle'
	    }, 0);
	    $('#hide-nav').toggleClass('collapsed');
	}

	function hideSidebarRight() {
		$('#sidebar-right').animate({
	        width: 'toggle'
	    }, 0);
	}

	// Tooltips
	$('.hover-info').tooltip();

	$('ul.nav').removeClass('nav-collapse');

	// Keywords
	//$('.field-name-field-keywords a').addClass('label label-info keywords');

	// Fade in actions when mouse over on comments
	$('.comment blockquote .actions a').fadeTo(500,.3);
	$('.comment blockquote').hover(function() {
		$('.comment blockquote .actions a').fadeTo(0, 1);
	}, function() {
		$('.comment blockquote .actions a').fadeTo(500,.3);
	});


	// Apply styles to elements - to change later
	$('ul.links a').addClass('btn btn-small');
	$('li.statistics_counter span').addClass('label');

	// style all images in the content area except the group images
	$('#content img').not('.view-display-id-all_public_groups_block a img, td.rowspan_bottom img, td.rowspan_top img, td.rowspan_top img, div.thumbnail img, img.img-polaroid, #content .group-image img, #block-druedu-layout-alter-user-picture img').addClass('img-polaroid');
	$('#block-druedu-layout-alter-user-picture img').addClass('img-circle');


	// ========================== Responsive JS

	// We need to find out if we're in 800x600 (presentation mode thought a projector)
	var sw = document.body.clientWidth,
		sh = document.body.clientHeight,
		breakpoint = 800,
		speed = 800,
		pres = true;

	pres = (sw > breakpoint) ? false : true;

	if (pres) {
		if ($('body').hasClass('front')) {

		} else {
			hideSidebarRight();
		}
	}

	(function(w){
		$(w).resize(function(){
			// Update dimensions on resize
			sw = document.body.clientWidth;
			sh = document.body.clientHeight;
			pres = (sw > breakpoint) ? false : true;
		});
	})(this);

		// add border to li on the pageination
	$('.pagination li.pager-ellipsis').next('li').css('border-left',"1px solid #ddd");

	// fix the dropdown click for ipad
	 $('body').on('touchstart.dropdown', '.dropdown-menu', function (e) { e.stopPropagation(); });

	//hide top-toolbar on ipad iphone when keyboard is display
	if(navigator.platform == 'iPad' || navigator.platform == 'iPhone' || navigator.platform == 'iPod')
 	{
 		$('input, textarea').on('focus', function(){
 			$('header').first().hide();
 			$('#toolbar').hide();
 		});
 		$('input, textarea').on('blur', function(){
 			$('header').first().show();
 			$('#toolbar').show();
 		});
 		for ( instance in CKEDITOR.instances ) {
  			CKEDITOR.instances[instance].on( 'focus', function( e ){
				$('header').first().hide();
				$('#toolbar').hide();
			});
			CKEDITOR.instances[instance].on( 'blur', function( e ){
				$('header').first().show();
				$('#toolbar').show();
			});
		}

		if($('#sidebar-right').length && $('#sidebar-right.show').length){
			$('#hide-sidebar .icon-columns').click();
		}
 	}
 	if(navigator.platform == 'iphone')
 	{
		if($('#sidebar-left').length && $('#sidebar-left.show').length){
			$('#hide-nav .icon-columns').click();
		}
 	}

});
