<?php
/*
 * curios.pages_default.inc
 * 
 * Copyright (c) 2011-2013, Stuart Taylor (staylor@abdn.ac.uk),
 * University of Aberdeen. All rights reserved.
 *
 * CURIOS: Linked Data CMS is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * Implements hook_default_page_manager_pages.
 *
 * Generates default panels pages for each browsing class in the configuration.
 *
 * Each page has two panel varients - the listings panel and the details panel. The listings panel
 * displays the listing view. The details panel uses the layout defined in curios.layouts.inc
 * to display the summary, field listing, gallery and relationships blocks.
 */
function curios_default_page_manager_pages() {
  if (!variable_get('ldcms_installed')) {
    return;
  }

  $config = curios_configuration();
  $pages = array();

  // For each view, create its panel page.
  foreach ($config->getViews() as $view_spec) {
    $pages[__panel_page_id($view_spec->getMachineName())] = __curios_generate_panel_page($view_spec);
  }
  
  return $pages;
}

/**
 * View name to panel page name mapping.
 */
function __panel_page_id($view_name) { return $view_name.'_panel_page'; }

/**
 * View name to panel varient name mapping.
 */
function __panel_varient_id($view_name, $varient_name) { return 'page_'.__panel_page_id($view_name).'_panel_context_'.$varient_name; }

/**
 * Generates the panel page for a browsing class.
 */
function __curios_generate_panel_page(&$view_spec) {
  $page = new stdClass;
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = __panel_page_id($view_spec->getMachineName());
  $page->task = 'page';
  $page->admin_title = $view_spec->getLabel();
  $page->admin_description = ' Panel Page: '. $view_spec->getLabel() .' ('. $view_spec->getMachineName() .')';
  $page->path = $view_spec->getPath().'/!args';
  $page->access = array(
    'logic' => 'and',
  );
  $page->menu = array(
    'type' => 'normal',
    'title' => $view_spec->getLabel(),
    'name' => 'menu-curios',
    'weight' => '0',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array(
    'args' => array(
      'id' => 1,
      'identifier' => 'args',
      'name' => 'string',
      'settings' => array('use_tail' => 1),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();

  // Listing panel.
  $listing_id = __panel_varient_id($view_spec->getMachineName(), 'listing');
  $page->default_handlers[$listing_id] = _curios_generate_listing_panel($view_spec, $listing_id);

  // Details panel.
  $details_id = __panel_varient_id($view_spec->getMachineName(), 'details');
  $page->default_handlers[$details_id] = _curios_generate_details_panel($view_spec, $details_id);

  return $page;
}

/**
 * Generates the listings panel varient.
 */
function _curios_generate_listing_panel(&$view_spec, $handler_id) {
  $handler = new stdClass;
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = $handler_id;
  $handler->task = 'page';
  $handler->subtask = __panel_page_id($view_spec->getMachineName());
  $handler->handler = 'panel_context';
  $handler->weight = 1;
  $handler->conf = array(
    'title' => 'Listing',
    'no_blocks' => 0,
    'pipeline' => 'ipe',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'context_exists',
          'settings' => array(
            'exists' => '0',
          ),
          'context' => 'argument_string_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display;
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->content = array();
  $display->panels = array();
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
    $pane = new stdClass;
    $pane->pid = 'listing_pane';
    $pane->panel = 'middle';
    $pane->type = 'views';
    $pane->subtype = $view_spec->getMachineName();
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '20',
      'pager_id' => '0',
      'offset' => '',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 1,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'listing',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'curios-listing',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['listing_pane'] = $pane;
    $display->panels['middle'][0] = 'listing_pane';
  $handler->conf['display'] = $display;

  return $handler;
}

/**
 * Generates the details panel varient.
 */
function _curios_generate_details_panel(&$view_spec, $hander_id) {
  $config = curios_configuration();
  $view = views_get_view($view_spec->getMachineName());
  
  $handler = new stdClass;
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = $hander_id;
  $handler->task = 'page';
  $handler->subtask = __panel_page_id($view_spec->getMachineName());
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  
$handler->conf = array(
  'title' => 'Details',
  'no_blocks' => 0,
  'pipeline' => 'ipe',
  'body_classes_to_remove' => '',
  'body_classes_to_add' => '',
  'css_id' => '',
  'css' => '',
  'contexts' => array(),
  'relationships' => array(),
  'access' => array(
    'logic' => 'and',
    'plugins' => array(
      0 => array(
        'name' => 'context_exists',
        'settings' => array(
          'exists' => '1',
        ),
        'context' => 'argument_string_1',
        'not' => FALSE,
      ),
   2 => array(
        'name' => 'php',
        'settings' => array(
          'description' => 'Record visibility',
          'php' => 'if  (user_access(\'curios view pending records\') || curios_is_visible($contexts["argument_string_1"]->data))
   return TRUE;
   else
   { 
    drupal_set_message("You do not have enough permission to view record ID:".$contexts["argument_string_1"]->data, \'error\');
    return FALSE;
   }
',
        ),
        'not' => FALSE,
      ),
    ),
  ),
);
  $display = new panels_display;
  $display->layout = 'flexible:ldcms_details_page_layout';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'admin_region' => NULL,
      'summary_region' => NULL,
      'properties_region' => NULL,
      'image_gallery_region' => NULL,
      'relationships_region' => NULL,
      'comment_region' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->content = array();
  $display->panels = array();
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;

  // Admin Region.
  $pane = new stdClass;
  $pane->pid = 'admin_pane';
  $pane->panel = 'admin_region';
  $pane->type = 'views';
  $pane->subtype = $view_spec->getMachineName(); // Name of view.
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_pager_settings' => 0,
    'use_pager' => 0,
    'nodes_per_page' => '0',
    'pager_id' => '0',
    'offset' => '0',
    'more_link' => 0,
    'feed_icons' => 0,
    'panel_args' => 1,
    'link_to_view' => 0,
    'args' => '',
    'url' => '',
    'display' => 'admin_tools',
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $display->content['admin_pane'] = $pane;
  $display->panels['admin_region'][0] = 'admin_pane';

  // Summary Region.
  $pane = new stdClass;
  $pane->pid = 'summary_pane';
  $pane->panel = 'summary_region';
  $pane->type = 'views';
  $pane->subtype = $view_spec->getMachineName(); // Name of view.
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_pager_settings' => 0,
    'use_pager' => 0,
    'nodes_per_page' => '0',
    'pager_id' => '0',
    'offset' => '0',
    'more_link' => 0,
    'feed_icons' => 0,
    'panel_args' => 1,
    'link_to_view' => 0,
    'args' => '',
    'url' => '',
    'display' => 'summary',
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $display->content['summary_pane'] = $pane;
  $display->panels['summary_region'][0] = 'summary_pane';

  // Properties Region.
  $pane = new stdClass;
  $pane->pid = 'properties_pane';
  $pane->panel = 'properties_region';
  $pane->type = 'views';
  $pane->subtype = $view_spec->getMachineName(); // Name of view.
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_pager_settings' => 0,
    'use_pager' => 0,
    'nodes_per_page' => '0',
    'pager_id' => '0',
    'offset' => '0',
    'more_link' => 0,
    'feed_icons' => 0,
    'panel_args' => 1,
    'link_to_view' => 0,
    'args' => '',
    'url' => '',
    'display' => 'properties',
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $display->content['properties_pane'] = $pane;
  $display->panels['properties_region'][0] = 'properties_pane';

  // Image Gallery Region.
  if (isset($view->display['images'])) {
    $pane = new stdClass;
    $pane->pid = 'image_gallery_pane';
    $pane->panel = 'image_gallery_region';
    $pane->type = 'views';
    $pane->subtype = $view_spec->getMachineName();
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '10',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 1,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'images',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['image_gallery_pane'] = $pane;
    $display->panels['image_gallery_region'][0] = 'image_gallery_pane';
  }


  // Comment Region.

  $pane = new stdClass();
  $pane->pid = 'comment_pane';
  $pane->panel = 'comment_region';
  $pane->type = 'custom';
  $pane->subtype = 'custom';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'admin_title' => '',
    'title' => '',
    'body' => ' <div id="disqus_thread"></div>
    <script type="text/javascript">
        /* * * CONFIGURATION VARIABLES: EDIT BEFORE PASTING INTO YOUR WEBPAGE * * */
        var disqus_shortname = \'curiosdemo\'; // required: replace example with your forum shortname

        /* * * DON\'T EDIT BELOW THIS LINE * * */
        (function() {
            var dsq = document.createElement(\'script\'); dsq.type = \'text/javascript\'; dsq.async = true;
            dsq.src = \'//\' + disqus_shortname + \'.disqus.com/embed.js\';
            (document.getElementsByTagName(\'head\')[0] || document.getElementsByTagName(\'body\')[0]).appendChild(dsq);
        })();
    </script>
    <noscript>Please enable JavaScript to view the <a href="http://disqus.com/?ref_noscript">comments powered by Disqus.</a></noscript>
    <a href="http://disqus.com" class="dsq-brlink">comments powered by <span class="logo-disqus">Disqus</span></a>
    ',
    'format' => 'full_html',
    'substitute' => 1,
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $display->content['comment_pane'] = $pane;
  $display->panels['comment_region'][0] = 'comment_pane';

 /* $pane = new stdClass;
  $pane->pid = 'comment_pane';
  $pane->panel = 'comment_region';
  $pane->type = 'views';
  $pane->subtype = $view_spec->getMachineName(); // Name of view.
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_pager_settings' => 0,
    'use_pager' => 0,
    'nodes_per_page' => '0',
    'pager_id' => '0',
    'offset' => '0',
    'more_link' => 0,
    'feed_icons' => 0,
    'panel_args' => 1,
    'link_to_view' => 0,
    'args' => '',
    'url' => '',
    'display' => 'properties',
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $display->content['comment_pane'] = $pane;
  $display->panels['comment_region'][0] = 'comment_pane';
*/
  // Relationships Region.
  $pane_index = 0;
  foreach ($view_spec->getObjectFields() as $field_id) {
    if ($field_id == $config->getImageRelationshipFieldId())
      continue;

    $resource = $view_spec->getResource();
    $resource_name = $resource->getMachineName();
    $field_name = $resource_name.'_'.$field_id;

    /* From curios_generate_object_attachment:
     *   $handler = $view->new_display('block', 'Object: '.$field->getLabel(), 'object_'.$field_name);
     *
     * TODO ensure this remains consistent: relationship view blocks are named "object_$field_name"
     */
    $relationship_block_name = 'object_'.$field_name;

    $pane = new stdClass;
    $pane->pid = $relationship_block_name.'_pane';
    $pane->panel = 'relationships_region';
    $pane->type = 'views';
    $pane->subtype = $view_spec->getMachineName(); // View name
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '10',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 1,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => $relationship_block_name,
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content[$relationship_block_name.'_pane'] = $pane;
    $display->panels['relationships_region'][$pane_index++] = $relationship_block_name.'_pane';
  }

  return $handler;
}
