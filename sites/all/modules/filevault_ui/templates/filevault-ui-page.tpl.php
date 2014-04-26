<?php

/**
 *  Filevault page Template
 *
 *  This template will render the filevault page.
 *
 *  Variables:
 *
 *  $fileobejcts           // Contains the type of object. Type is based on mime type
 *
 */

/*
                <?php foreach ($fileObejcts as $delta => $file) : ?>
                <?php print render($fileObejcts); ?>
                <?php endforeach; ?>
 */
?>

<div class="container-fluid">

        <!-- Top toolbar -->
        <div class="row-fluid">
          <div class="span6 offset2">
                <div class="type-selector btn-group" data-toggle="buttons-checkbox">
                    <button type="button" class="btn" data-type="image"><i class="icon-camera"></i> Photos</button>
                    <button type="button" class="btn" data-type="video"><i class="icon-film"></i> Movies</button>
                    <button type="button" class="btn" data-type="audio"><i class="icon-headphones"></i> Audio</button>
                    <button type="button" class="btn" data-type="document"><i class="icon-file"></i> Documents</button>
                </div>
            </div>
            <div class="span4">
                <form class="form-search pull-right">
                    <input type="text" class="input-medium search-query">
                    <button type="submit" class="btn">Search</button>
                </form>
            </div>
        </div>

        <!-- Sidebar -->
        <div class="row-fluid">
            <div class="span2">
                <div><?php print $path; ?></div>
                <div class="fileinfo">
                	<form>
                      <fieldset>
                        <legend>File info</legend>
                        <label>Name</label>
                        <input type="text" placeholder="Type something…" class="filename">
                        <div><span>Size:</span><span class="filesize"></span></div>
                        <label class="checkbox">
                          <input type="checkbox"> Public
                        </label>

                        <div class="input-append">
  							<input placeholder="Username…" id="shareuser" type="text">
  							<button class="btn" type="button">Share</button>
						</div>


                        <button type="submit" class="save btn">Save</button>
                        <button type="submit" class="delete btn btn-danger">Delete</button>
                      </fieldset>
                    </form>
                </div>
            </div>

            <!-- Main content -->
            <div class="span10">

                <?php if (!$filesfound): ?>
                    <div class="nofilesfound">
                        <h2>No files or directories found in this directory</h2>
                    </div>
                <?php endif; ?>

                <?php if ($filesfound): ?>
                    <ul class="fw_filelist">
                        <?php foreach ($fileobjects as $file) : ?>
                            <li class="fw_file">
                                <?php print theme('filevault_ui_fileobject', array('fileobject' => $file, 'display' => 'icon', 'path'=> $path)); ?>
                            </li>
                        <?php endforeach; ?>
                    </ul>
                <?php endif; ?>
            </div>
        </div>

</div>

