<?php

/**
* @file
    * Default theme implementation to present all user profile data.
*
    * This template is used when viewing a registered member's profile page,
* e.g., example.com/user/123. 123 being the users ID.
*
    * Use render($user_profile) to print all profile items, or print a subset
* such as render($user_profile['user_picture']). Always call
    * render($user_profile) at the end in order to print all remaining items. If
* the item is a category, it will contain all its profile items. By default,
* $user_profile['summary'] is provided, which contains data on the user's
    * history. Other data can be included by modules. $user_profile['user_picture']
* is available for showing the account picture.
    *
* Available variables:
*   - $user_profile: An array of profile items. Use render() to print them.
    *   - Field variables: for each field instance attached to the user a
*     corresponding variable is defined; e.g., $account->field_example has a
    *     variable $field_example defined. When needing to access a field's raw
*     values, developers/themers are strongly encouraged to use these
*     variables. Otherwise they will have to explicitly specify the desired
    *     field language, e.g. $account->field_example['en'], thus overriding any
*     language negotiation rule that was previously applied.
    *
* @see user-profile-category.tpl.php
    *   Where the html is handled for the group.
* @see user-profile-item.tpl.php
    *   Where the html is handled for each item in the group.
* @see template_preprocess_user_profile()
    */
//HELP
//Use dpm($user_profile); Outputs the content variable for inspection.
//General principle to alter classes: access $user_profile['field_name']['#attributes']['class'];
//Example - add a classe to a field wrapper: $user_profile['field_firstname ']['#attributes']['class'][] = 'my_class';
//Please place the class alteration at the beginning of this template - eventually, they will belong to druedu_layout_alter_user_view()
//Adding a variation of this template: create a node--content_type_machine_name.tpl.php file
?>
<div class="pro-middle">
    <div class="user-name">
        <?php print render($user_profile['field_firstname']); ?>
        <?php print render($user_profile['field_lastname']); ?>
    </div>

    <div class="user-info">
         <?php print render($user_profile['og_user_group_ref']); ?>
        <?php print render($user_profile['field_position']); ?>
        <?php print render($user_profile['field_speaks']); ?>
    </div>
    <?php $field_displayed = array('field_firstname', 'field_lastname', 'field_position', 'summary', 'og_user_group_ref','field_speaks'); ?>
    <?php $first_open = FALSE; ?>
    <div class="accordion" id="accordion2">
        <?php foreach($user_profile as $id => $field): ?>
            <?php if(!in_array($id, $field_displayed)): ?>
                <div class="accordion-group">
                    <div class="accordion-heading">
                        <a class="accordion-toggle" data-toggle="collapse" data-parent="#accordion2" href="#collapse<?php print $id ?>">
                            <i class="icon-<?php print $id ?>"></i><span><?php print $field['#title'];?></span>
                        </a>
                    </div>
                    <div id="collapse<?php print $id ?>" class="accordion-body <?php (!$first_open)? print 'in' : '';?> collapse">
                        <div class="accordion-inner">
                            <?php print render($user_profile[$id]); ?>
                        </div>
                    </div>
                </div>
            <?php $first_open = TRUE; ?>
            <?php endif; ?>
        <?php endforeach; ?>
    </div>
</div>