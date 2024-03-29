/**
 * @file feedback.js
 *
 * Initiates the html2canvas library.
 */
(function ($, Drupal, win, doc) {
  // log proxy function
  function log (msg) {
    win.console.log( msg );
  }
  // function to remove elements, input as arrays
  function removeElements (remove) {
    for (var i = 0, len = remove.length; i < len; i++ ) {
      var item = Array.prototype.pop.call( remove );
      if ( item !== undefined ) {
        if (item.parentNode !== null ) { // check that the item was actually added to DOM
          item.parentNode.removeChild( item );
        }
      }
    }
  }
  function getBounds (el) {
    return el.getBoundingClientRect();
  }
  function emptyElements(el) {
    var item;
    while( (( item = el.firstChild ) !== null ? el.removeChild( item ) : false) ) {}
  }
  function element (name, text) {
    var el = doc.createElement( name );
    el.appendChild( doc.createTextNode( text ) );
    return el;
  }
  // script onload function to provide support for IE as well
  function scriptLoader (script, func) {
    if (script.onload === undefined) {
      // IE lack of support for script onload
      if (script.onreadystatechange !== undefined) {
        var intervalFunc = function() {
        if (script.readyState !== "loaded" && script.readyState !== "complete") {
        win.setTimeout( intervalFunc, 250 );
      } else {
        // it is loaded
        func();
      }
    };

    win.setTimeout( intervalFunc, 250 );

    } else {
      log("ERROR: We can't track when script is loaded");
    }
    } else {
      return func;
    }
  }
  var h2cQueue,
      h2cCanvas,
      h2cDone = false,
      clickDone = false,
      fcAvailable,
      html2obj,
      canvasHolder,
      blackoutBox,
      highlightBox,
      highlightClose,
      nextButton,
      body,
      CANVAS = "canvas",
      DIV = "div",
      H2C_IGNORE = "data-html2canvas-ignore",
      PX = "px",
      highlightContainer,
      mouseMoveEvent,
      modalBody,
      message,
      mouseClickEvent,
      mouseDownEvent,
      mouseUpEvent,
      drawBox,
      mouseDrawEvent,
      closeButton,
      dataExclude = "data-exclude",
      h2cAvailable;

  var Feedback = {
        /**
         * options
         * string h2cPath
         * string fcPath
         * string label - Button label text, default "Send Feedback"
         * string labelClass - Button class(es), default "btn bottom-right"
         * string closeClass - Close class(es), default "close"
         * string closeLabel
         * string modalClass
         * string modalHeader
         * string modalHeaderClass
         * string modalIntro
         * string buttonClass
         * Element appendTo - where to append button, default doc.body
         */

        debug: true,
        log: log,

        init: function( options ) {
            var button,
            modal,
            body = doc.body,
            glass = doc.createElement(DIV),
            returnMethods = {
                // open send feedback modal window
                open: function() {
                    var modalHeader = doc.createElement(DIV),
                    modalFooter = doc.createElement(DIV),
                    script,
                    // execute the html2canvas script
                    runH2c = function(){
                        try {

                            options.onrendered = options.onrendered || function( canvas ) {
                                h2cCanvas = canvas;

                                //           window.setTimeout(function(){
                                h2cDone = true;
                                nextFunc();
                            //     }, 3000);


                            };

                            html2obj = win.html2canvas([ doc.body ], options);


                        } catch( e ) {

                            h2cDone = true;
                            nextFunc();
                            log("Error in html2canvas: " + e.message);
                        }
                    },
                    // Close button
                    a = element("a", options.closeLabel || "×");

                    modalBody = doc.createElement(DIV);

                    body.appendChild( glass );

                    // user message
                    message = doc.createElement("textarea");

                    if ( win.html2canvas === undefined && script === undefined ) {

                        // let's load html2canvas library while user is writing message

                        script = doc.createElement("script");
                        script.src = options.h2cPath || "libs/html2canvas.js";
                        script.onerror = function() {
                            h2cAvailable = false;
                            log("Failed to load html2canvas library, check that the path is correctly defined");
                        };

                        script.onload = (scriptLoader)(script, function() {

                            if (win.html2canvas === undefined) {
                                log("Loaded html2canvas, but library not found");
                                h2cAvailable = false;
                                return;
                            }

                            win.html2canvas.logging = win.Feedback.debug;
                            runH2c();

                            h2cAvailable = true;
                        });

                        button.parentNode.appendChild( script );
                    } else {
                        // html2canvas already loaded, just run it then
                        runH2c();
                    }

                    a.className =  options.closeClass || "close";
                    a.onclick = returnMethods.close;
                    a.href = "#";

                    button.disabled = true;


                    modalHeader.appendChild( a );
                    modalHeader.appendChild( element("h3", options.modalHeader || "Send Feedback" ) );

                    modalHeader.className =  "feedback-header";


                    modalBody.className = "feedback-body";

                    modalBody.appendChild( element("p", options.modalIntro || "Please describe the issue you are experiencing") );

                    modalBody.appendChild( message );


                    // Next button
                    nextButton = element( "button", options.nextLabel || "Continue" );

                    nextButton.className =  options.buttonClass || "btn";
                    nextButton.onclick = function() {
                        clickDone = true;
                        nextButton.disabled = true;

                        emptyElements( modalBody ); // clear it of all elements

                        nextFunc();

                    };

                    function nextFunc() {

                        var progressBar,
                        action = true; // true highlight, false blackout

                        if ( clickDone ) {

                            nextButton.onclick = function( e ) {
                                e.preventDefault();

                                // remove event listeners
                                body.removeEventListener("mousemove", mouseMoveEvent, false);
                                body.removeEventListener("click", mouseClickEvent, false);
                                body.removeEventListener("click", mouseDownEvent, false);

                                returnMethods.review();



                            };
                        }

                        // canvas ready and user has entered message
                        if (h2cDone && clickDone) {
                            nextButton.disabled = false;

                            var timer,
                            removeElement,
                            ctx,
                            buttonClickFunction = function( e ) {
                                e.preventDefault();
                                blackoutButton.classList.toggle("active");
                                highlightButton.classList.toggle("active");
                                action = !action;
                            },
                            clearBox = function() {
                                blackoutBox.style.left =  "-5px";
                                blackoutBox.style.top =  "-5px";
                                blackoutBox.style.width = "0px";
                                blackoutBox.style.height = "0px";
                                blackoutBox.setAttribute(dataExclude, true);


                                highlightBox.style.left =  "-5px";
                                highlightBox.style.top =  "-5px";
                                highlightBox.style.width = "0px";
                                highlightBox.style.height = "0px";
                                highlightBox.setAttribute(dataExclude, true);

                                win.clearTimeout( timer );
                            },
                            hideClose = function() {
                                highlightClose.style.left =  "-50px";
                                highlightClose.style.top =  "-50px";

                            },
                            blackoutButton = element("a", "Blackout"),
                            highlightButton = element("a", "Highlight"),
                            previousElement;

                            // delegate mouse move event for body
                            mouseMoveEvent = function(e) {

                                return;
                                // set close button
                                if ( e.target !== previousElement && (e.target.classList.contains("feedback-blackedout") || e.target.classList.contains("feedback-highlighted"))) {

                                    var left = (parseInt(e.target.style.left, 10) +  parseInt(e.target.style.width, 10));
                                    left = Math.max( left, 10 );

                                    left = Math.min( left, win.innerWidth - 15 );

                                    var top = (parseInt(e.target.style.top, 10));
                                    top = Math.max( top, 10 );

                                    highlightClose.style.left = left + PX;
                                    highlightClose.style.top = top + PX;
                                    removeElement = e.target;
                                    clearBox();
                                    previousElement = undefined;
                                    return;
                                }

                                // don't do anything if we are highlighting a close button or body tag
                                if (e.target.nodeName === "BODY" ||  e.target === highlightClose || e.target === modal || e.target === nextButton || e.target.parentNode === modal || e.target.parentNode === modalHeader) {
                                    // we are not gonna blackout the whole page or the close item
                                    clearBox();
                                    previousElement = e.target;
                                    return;
                                }

                                hideClose();

                                if (e.target !== previousElement ) {
                                    previousElement = e.target;

                                    win.clearTimeout( timer );

                                    timer = win.setTimeout(function(){
                                        var bounds = getBounds( previousElement ),
                                        item;

                                        if ( action === false ) {
                                            item = blackoutBox;
                                        } else {
                                            item = highlightBox;
                                            item.width = bounds.width;
                                            item.height = bounds.height;
                                            ctx.drawImage(h2cCanvas, win.pageXOffset + bounds.left, win.pageYOffset + bounds.top, bounds.width, bounds.height, 0, 0, bounds.width, bounds.height );
                                        }

                                        // we are only targetting IE>=9, so window.pageYOffset works fine
                                        item.setAttribute(dataExclude, false);
                                        item.style.left = win.pageXOffset + bounds.left + PX;
                                        item.style.top = win.pageYOffset + bounds.top + PX;
                                        item.style.width = bounds.width + PX;
                                        item.style.height = bounds.height + PX;
                                    }, 100);
                                }
                            };
                            // delegate event for body click
                            mouseDownEvent = function (e) {
                              if (button.disabled === false || closeButton === true) {
                                  return;
                              }

                              e.preventDefault();

                              body.addEventListener('mouseup', mouseUpEvent, false);
                              body.addEventListener('mousemove', mouseDrawEvent, false);
                              drawBox = drawBox || {};
                              drawBox.startX = e.pageX;
                              drawBox.startY = e.pageY;
                              var blackout = doc.createElement(DIV);
                              var boxClass = action === false ? 'feedback-blackedout' : 'feedback-highlighted';
                              blackout.classList.add(boxClass);
                              blackout.style.left = drawBox.startX + 'px';
                              blackout.style.top = drawBox.startY + 'px';
                              blackout.style.width = '0px';
                              blackout.style.height = '0px';

                              body.appendChild( blackout );
                              drawBox.element = blackout;
                              previousElement = undefined;
                            };
                            mouseUpEvent = function (e) {
                              if (Math.abs(drawBox.startY - e.pageY) < 20 || Math.abs(drawBox.startX - e.pageX) < 20) {
                                drawBox.element.parentNode.removeChild( drawBox.element );
                              }
                              body.removeEventListener('mouseup', mouseUpEvent, false);
                              body.removeEventListener('mousemove', mouseDrawEvent, false);
                              if ( action !== false || true ) {
                                //ctx = drawBox.element.getContext("2d");
                                drawBox.element.classList.add("feedback-highlight-element");

                                var screen = doc.createElement( CANVAS );
                                var sCTX = screen.getContext('2d');
                                screen.width = h2cCanvas.width;
                                screen.height = h2cCanvas.height;

                                sCTX.fillStyle = 'rgba(80,80,80,.5)';
                                sCTX.fillRect( 0, 0, h2cCanvas.width, h2cCanvas.height );

                                sCTX.globalCompositeOperation = 'destination-out';
                                $('.feedback-highlight-element').each(function (){
                                  var d = [];
                                  d.left = $(this).offset().left;
                                  d.top = $(this).offset().top;
                                  d.height = $(this).height();
                                  d.width = $(this).width();
                                  sCTX.fillStyle = '#FFFFFF';
                                  sCTX.fillRect(d.left, d.top, d.width, d.height);
                                });

                                body.appendChild(screen);
                                $(screen).addClass('feedback-canvas');
                                $('#screen').remove();
                                $(screen).attr('id', 'screen');
                                $('.feedback-glass').remove();
                                $(screen).css('z-index', 2000);
                              }
                              highlightClose = element(DIV, "×");

                              highlightClose.id = "feedback-highlight-close";

                              highlightClose.addEventListener("click", function(){
                                  this.parentNode.parentNode.removeChild( this.parentNode );
                                  hideClose();
                              }, false);
                              drawBox.element.appendChild( highlightClose );

                            };
                            mouseDrawEvent = function (e) {
                              if (e.pageX > drawBox.startX) {
                                drawBox.element.style.width = e.pageX - drawBox.startX + 'px';
                                drawBox.element.style.left = drawBox.startX + 'px';
                              } else {
                                drawBox.element.style.width = drawBox.startX - e.pageX + 'px';
                                drawBox.element.style.left = e.pageX + 'px';
                              }
                              if (e.pageY > drawBox.startY) {
                                drawBox.element.style.height = e.pageY - drawBox.startY + 'px';
                                drawBox.element.style.top = drawBox.startY + 'px';
                              } else {
                                drawBox.element.style.height = drawBox.startY - e.pageY + 'px';
                                drawBox.element.style.top = e.pageY + 'px';
                              }

                            };
                            mouseClickEvent = function( e ){
                                if (button.disabled === false) {
                                    return;
                                }

                                return;

                                e.preventDefault();


                                if ( action === false) {
                                    if ( blackoutBox.getAttribute(dataExclude) === "false") {
                                        var blackout = doc.createElement(DIV);
                                        blackout.classList.add('feedback-blackedout');
                                        blackout.style.left = blackoutBox.style.left;
                                        blackout.style.top = blackoutBox.style.top;
                                        blackout.style.width = blackoutBox.style.width;
                                        blackout.style.height = blackoutBox.style.height;

                                        body.appendChild( blackout );
                                        previousElement = undefined;
                                    }
                                } else {
                                    if ( highlightBox.getAttribute(dataExclude) === "false") {

                                        highlightBox.classList.add('feedback-highlighted');
                                        highlightBox.classList.remove('feedback-highlight-element');
                                        highlightBox = doc.createElement('canvas');

                                        ctx = highlightBox.getContext("2d");

                                        highlightBox.classList.add("feedback-highlight-element");

                                        body.appendChild( highlightBox );
                                        clearBox();
                                        previousElement = undefined;
                                    }
                                }
                            };
                            modal.classList.add('feedback-animate-toside');

                            blackoutBox = doc.createElement('div');
                            highlightBox = doc.createElement( CANVAS );
//                            blackoutBox = doc.createElement('div');
//                            highlightBox = doc.createElement( CANVAS );
//
//                            ctx = highlightBox.getContext("2d");
//
//                            highlightClose = element(DIV, "×");
//                            highlightContainer = doc.createElement('div');
//
//                            highlightClose.id = "feedback-highlight-close";
//
//                            highlightClose.addEventListener("click", function(){
//                                removeElement.parentNode.removeChild( removeElement );
//                                hideClose();
//                            }, false);
//
//                            body.appendChild( highlightClose );

                            ctx = highlightBox.getContext("2d");

                            highlightClose = element(DIV, "×");
                            highlightContainer = doc.createElement('div');

                            highlightClose.id = "feedback-highlight-close";

                            highlightClose.addEventListener("click", function(){
                                removeElement.parentNode.removeChild( removeElement );
                                hideClose();
                            }, false);

                            body.appendChild( highlightClose );

                            h2cCanvas.classList.add('feedback-canvas');

                            body.appendChild( h2cCanvas);

                            var buttonItem = [ highlightButton, blackoutButton ];

                            modalBody.appendChild( element("p", "Highlight or blackout important information") );

                            // add highlight and blackout buttons
                            for (var i = 0; i < 2; i++ ) {
                                buttonItem[ i ].classList.add('btn');
                                buttonItem[ i ].classList.add('btn-small');
                                buttonItem[ i ].classList.add( i === 0 ? 'active' : 'btn-inverse');

                                buttonItem[ i ].href = "#";
                                buttonItem[ i ].onclick = buttonClickFunction;

                                modalBody.appendChild( buttonItem[ i ] );

                                modalBody.appendChild( doc.createTextNode(" ") );

                            }

                            highlightContainer.id = "feedback-highlight-container";
                            highlightContainer.style.width = h2cCanvas.width + PX;
                            highlightContainer.style.height = h2cCanvas.height + PX;
//                            highlightContainer.id = "feedback-highlight-container";
//                            highlightContainer.style.width = h2cCanvas.width + PX;
//                            highlightContainer.style.height = h2cCanvas.height + PX;
//
//                            highlightBox.classList.add("feedback-highlight-element");
//                            blackoutBox.id = "feedback-blackout-element";
//                            body.appendChild( highlightBox );
//                            highlightContainer.appendChild( blackoutBox );
//
//                            body.appendChild( highlightContainer );

                            highlightBox.classList.add("feedback-highlight-element");
                            blackoutBox.id = "feedback-blackout-element";
                            body.appendChild( highlightBox );
                            highlightContainer.appendChild( blackoutBox );

                            body.appendChild( highlightContainer );

                            // bind mouse delegate events
                            body.addEventListener("mousemove", mouseMoveEvent, false);
                            body.addEventListener("click", mouseClickEvent, false);
                            body.addEventListener('mousedown', mouseDownEvent, false);

                        } else if ( clickDone ) {

                        }
                    }
                    modalFooter.className = "feedback-footer";
                    modalFooter.appendChild( nextButton );

                    // modal container
                    modal = doc.createElement(DIV);
                    modal.className =  options.modalClass || "modalfeedback";
                    modal.setAttribute(H2C_IGNORE, true); // don't render in html2canvas
                    modal.appendChild( modalHeader );
                    modal.appendChild( modalBody );
                    modal.appendChild( modalFooter );
                    button.parentNode.appendChild( modal );
                },
                // review the gathered data
                review: function() {

                    $('#screen').remove();
                    body.removeEventListener("mousedown", mouseDownEvent, false);
                    body.removeEventListener("mousemove", mouseDrawEvent, false);
                    body.removeEventListener("mouseup", mouseUpEvent, false);
                    modal.classList.add("feedback-animate-review");
                    emptyElements( modalBody );

                    var browserSpecs = doc.createElement(DIV);
                    var allowedSpecs = ["appName", "product", "appVersion", "cookieEnabled", "vendor", "appCodeName", "userAgent"];
                    var toSend = {};

                    if ( h2cCanvas !== undefined ) {
                        var ctx = h2cCanvas.getContext("2d"),
                        canvasCopy,
                        copyCtx,
                        radius = 5;
                        ctx.fillStyle = "#000";

                        // draw blackouts
                        Array.prototype.slice.call(doc.getElementsByClassName('feedback-blackedout'), 0).forEach( function( item ) {
                            var bounds = getBounds( item );
                            ctx.fillRect( bounds.left, bounds.top, bounds.width, bounds.height );
                            body.removeChild( item );

                        });

                        var items = Array.prototype.slice.call(doc.getElementsByClassName('feedback-highlighted'), 0);

                        if (items.length > 0 ) {

                            // copy canvas
                            canvasCopy = doc.createElement( CANVAS );
                            copyCtx = canvasCopy.getContext('2d');
                            canvasCopy.width = h2cCanvas.width;
                            canvasCopy.height = h2cCanvas.height;

                            copyCtx.drawImage(h2cCanvas, 0, 0);

                            ctx.fillStyle = "#777";
                            ctx.globalAlpha = 0.5;
                            ctx.fillRect( 0, 0, h2cCanvas.width, h2cCanvas.height );

                            ctx.beginPath();

                            items.forEach( function( item ) {
                                var bounds = getBounds( item );

                                var x = parseInt(item.style.left, 10),
                                y = parseInt(item.style.top, 10),
                                width = parseInt(item.style.width, 10),
                                height = parseInt(item.style.height, 10);

                                ctx.moveTo(x + radius, y);
                                ctx.lineTo(x + width - radius, y);
                                ctx.quadraticCurveTo(x + width, y, x + width, y + radius);
                                ctx.lineTo(x + width, y + height - radius);
                                ctx.quadraticCurveTo(x + width, y + height, x + width - radius, y + height);
                                ctx.lineTo(x + radius, y + height);
                                ctx.quadraticCurveTo(x, y + height, x, y + height - radius);
                                ctx.lineTo(x, y + radius);
                                ctx.quadraticCurveTo(x, y, x + radius, y);
                                body.removeChild( item );

                            });
                            ctx.closePath();
                            ctx.clip();

                            ctx.globalAlpha = 1;

                            ctx.drawImage(canvasCopy, 0,0);
                            removeElements( [ glass ] );
                        }

                        canvasCopy = doc.createElement( CANVAS );
                        copyCtx = canvasCopy.getContext('2d');
                        canvasCopy.width = 300;
                        canvasCopy.height = Math.round(h2cCanvas.height * (canvasCopy.width / h2cCanvas.width));

                        copyCtx.drawImage(h2cCanvas, 0, 0, h2cCanvas.width, h2cCanvas.height, 0, 0, canvasCopy.width, canvasCopy.height);
                        modalBody.appendChild( canvasCopy );

                        nextButton.firstChild.nodeValue = "Send form";

                        if (nextButton.className == 'btn') {
                          nextButton.className = 'btn send';
                        }

                        h2cCanvas.classList.add("feedback-canvas-complete");

                        browserSpecs.style.height = canvasCopy.height + 20 + PX;
                    }

                    browserSpecs.classList.add("feedback-browser");
                    browserSpecs.appendChild(element("h3", "Browser information"));

                    toSend.browserSpecs = {};

                    for (i in window.navigator) {
                        if (allowedSpecs.indexOf(i) != -1) {
                            browserSpecs.appendChild(element("p", i + ': ' + window.navigator[i]));
                            toSend.browserSpecs[i] = window.navigator[i];
                        }
                    }
                    modalBody.appendChild( browserSpecs );

                    modalBody.appendChild( element("p", options.modalIntro || "Please describe the issue you are experiencing") );

                    modalBody.appendChild( message );

                    jQuery('button.send').once().click(function(e) {
                        e.preventDefault();

                        var btn = jQuery(this);
                        btn.removeClass('send').addClass('sending');

                        nextButton.firstChild.nodeValue = "Sending...";

                        toSend.image = h2cCanvas.toDataURL();
                        toSend.message = jQuery('div.feedback-body textarea').val();
                        toSend.url = location.href;
                        jQuery.ajax({
                            url: Drupal.settings.basePath + 'livefeedback/post',
                            type: "POST",
                            data: toSend,
                            success: function(data) {
                                jQuery('.modalfeedback a.close').click();
                                nextButton.firstChild.nodeValue = "Send form";
                            },
                            error: function(data) {
                              alert("Oops! Something went wrong, reload the page!");
                            }
                        });
                    });
                },
                // close modal window
                close: function() {
                    $('#screen').remove();
                    body.removeEventListener("mousedown", mouseDownEvent, false);
                    body.removeEventListener("mousemove", mouseDrawEvent, false);
                    body.removeEventListener("mouseup", mouseUpEvent, false);
                    button.disabled = false;
                    h2cDone = false;
                    clickDone = false;

                    // remove feedback elements

                    removeElements( [ modal, glass, blackoutBox, highlightBox, highlightClose, highlightContainer, h2cCanvas ] );
                    removeElements( doc.getElementsByClassName('feedback-blackedout') );
                    removeElements( doc.getElementsByClassName('feedback-highlighted') );

                    // remove event listeners
                    body.removeEventListener("mousemove", mouseMoveEvent, false);
                    body.removeEventListener("click", mouseClickEvent, false);

                    h2cCanvas = undefined;

                    return false;

                }
            };

            glass.classList.add("feedback-glass");
            glass.style.pointerEvents = "none";
            glass.setAttribute(H2C_IGNORE, true);

            options = options || {};

            button = element("button", options.label || "Send Feedback");
            button.className = options.labelClass || "btn bottom-right";

            button.setAttribute(H2C_IGNORE, true);

            button.onclick = returnMethods.open;

            ((options.appendTo !== undefined) ? options.appendTo : doc.body).appendChild( button );
        }
    };

	Drupal.behaviors.livefeedback = {
		attach: function (context, settings) {
			if (Feedback !== undefined && typeof Feedback === 'object') {
	  		Feedback.init();
	  	}
		}
	};
}(jQuery, Drupal, window, document));
