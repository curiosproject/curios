<?php
/*
 * curios.views_default.inc
 * 
 * Copyright (c) 2011-2014,  Hai Nguyen (hai.nguyen@abdn.ac.uk) & Stuart Taylor (staylor@abdn.ac.uk),
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

require_once('includes/curios_ldcms.inc');
require_once('includes/curios.views_custom.inc');

/**
 * Implements hook_views_default_views.
 *
 * Generates a default set of views based on the configuration.
 *
 * Each browsing class has a:
 *   master view - defines fields and relationships used in other views.
 *   listing view - the listings/search page.
 *   summary block - provide a summary of an individual - title and description.
 *   properties block - literal field value listing.
 *   images block - image gallery block.
 *   object block - display relationship links, one block per relationship.
 *
 * The structure of the $view object is not currently well documented for the Views API. Generally the parameters can be
 * found by using the View UI to create/edit a view, then using the export function to examine the generated views objects.
 *
 * This function will also attempt to load pre-defined views exports from files named with the format: views/VIEW-ID.view.inc
 */
function curios_views_default_views() {
  if (!variable_get('ldcms_installed')) {
    return;
  }

  $config = curios_configuration();
  $views = array();
  $exports_path = drupal_get_path('module', 'curios') . '/views';
  $use_exports = FALSE;

  foreach ($config->getViews() as $view_name=>$view_spec) {
    $view_file = $view_spec->getMachineName().'.view.inc';
    $view_path = $exports_path.'/'.$view_file;
    
    // If an exported view exists in /views/view_name.view.inc
    // then import that view.
    // Otherwise the default view is generated is generated from the view spec.
    if ($use_exports && file_exists($view_path)) {
      include_once $view_path;
      $views[$view_name] = $view;
    } else {
      $views[$view_name] = __curios_generate_default_view($view_spec);
      $views[$view_name.'_update'] = __curios_generate_default_view_for_update($view_spec);
    }
  }
  return $views;
}


/**
 * Format field labels.
 */
function __format_name($name) { return _curios_split_camel_case($name); }

function _curios_table_id($resource_name) {
  $select = db_select('sparql_views_resource_type_endpoint', 'ep')
      ->fields('ep', array('endpoint_uri'));
  $select->join('sparql_views_resource_type', 'svrt', 'svrt.id = ep.svid AND svrt.name = :name', array(':name' => $resource_name));
  $rs = $select->execute()->fetchAssoc();
  $endpoint = sparql_views_get_endpoint($rs['endpoint_uri']);
  return $endpoint->table_id;
}

function _curios_get_table_id_from_uri($uri) {
  $endpoint = sparql_views_get_endpoint($uri);
  return $endpoint->table_id;
}

/**
 * Generates the default set of update view of view displays for a browsing class.
 */
function __curios_generate_default_view_for_update(&$view_spec) {
  $config = curios_configuration();

  $resource_name = $view_spec->getResource()->getMachineName();

  // change the query endpoint to noinference service
  $config_endpoints = $config->getEndpoints();
  $table_id = _curios_get_table_id_from_uri($config_endpoints['noinference']['query']);

  $view = new view;
  $view->name = $view_spec->getMachineName().'_update';
  $view->human_name = $view_spec->getLabel().'_update';
  $view->description = $view_spec->getLabel() .' ('. $view_spec->getMachineName().'_update' .')'.' for update endpoint (no inference)';
  $view->base_table = $table_id;
  $view->tag = 'CURIOS';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE;
  
  // Base fields: URI, dc:title, dc:description.
  $base_fields = array(
    'title'       => $resource_name.'_'.$config->getTitleFieldId(),
    'description' => $resource_name.'_'.$config->getDescriptionFieldId());

  // CURIOS options
  $view->curios_options['resource_name'] = $resource_name; // Not used currently, config has mapping view_name => resource_name

  // Primary views for updateform.
  __curios_generate_display('master', $view, $view_spec, $base_fields);
  // no pending records for "all records"  
  if ($resource_name != $config->getDefaultResourceId())
	  __curios_generate_display('pending_records', $view, $view_spec, $base_fields);

  __curios_generate_display('summary', $view, $view_spec, $base_fields);
  __curios_generate_display('properties', $view, $view_spec, $base_fields);
  __curios_generate_display('images', $view, $view_spec, $base_fields);
  __curios_generate_display('admin_tools', $view, $view_spec, $base_fields);
  __curios_generate_display('record_meta', $view, $view_spec, $base_fields);

  // Relationship blocks.
  foreach ($view_spec->getObjectFields() as $field_id) {
  //  if ($field_id == $config->getImageRelationshipFieldId())
  //    continue;

    __curios_generate_object_block($view, $view_spec, $base_fields, $field_id);
  }

  return $view;
}

/**
 * Generates the default set of view displays for a browsing class.
 */
function __curios_generate_default_view(&$view_spec) {
  $config = curios_configuration();

  $resource_name = $view_spec->getResource()->getMachineName();
  $table_id = _curios_table_id($resource_name);

  $view = new view;
  $view->name = $view_spec->getMachineName();
  $view->human_name = $view_spec->getLabel();
  $view->description = $view_spec->getLabel() .' ('. $view_spec->getMachineName() .')';
  $view->base_table = $table_id;
  $view->tag = 'CURIOS';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE;
  
  // Base fields: URI, dc:title, dc:description.
  $base_fields = array(
    'title'       => $resource_name.'_'.$config->getTitleFieldId(),
    'description' => $resource_name.'_'.$config->getDescriptionFieldId());

  // CURIOS options
  $view->curios_options['resource_name'] = $resource_name; // Not used currently, config has mapping view_name => resource_name

  // Primary views.
  __curios_generate_display('master', $view, $view_spec, $base_fields);
  // no listing view for "all records"  
  if ($resource_name != $config->getDefaultResourceId())
	  __curios_generate_display('listing', $view, $view_spec, $base_fields);
  __curios_generate_display('summary', $view, $view_spec, $base_fields);
  __curios_generate_display('properties', $view, $view_spec, $base_fields);
  __curios_generate_display('images', $view, $view_spec, $base_fields);
  __curios_generate_display('admin_tools', $view, $view_spec, $base_fields);
  __curios_generate_display('record_meta', $view, $view_spec, $base_fields);

  // Relationship blocks.
  foreach ($view_spec->getObjectFields() as $field_id) {
    if ($field_id == $config->getImageRelationshipFieldId())
      continue;

    __curios_generate_object_block($view, $view_spec, $base_fields, $field_id);
  }

  return $view;
}

/**
 * Generate a specific view display.
 *
 * This function executes the appropriate function to create a specific view display. These functions can be overridden
 * on a per-resource basis. Default views are defined in functions named with:
 *   __curios_generate_display_VIEW-ID_default
 * These can be overridden for a particular resource by functions named with:
 *   __curios_generate_display_VIEW-ID_RESOURCE-ID
 */
function __curios_generate_display($view_name, &$view, &$view_spec, $base_fields, $default = FALSE) {
    $resource_name = $view_spec->getResource()->getMachineName();

    $override_function = "__curios_generate_display_{$view_name}_{$resource_name}";
    $default_function = "__curios_generate_display_{$view_name}_default";

    if (!$default && function_exists($override_function)) {
      return call_user_func($override_function, $view, $view_spec, $base_fields);
    } else {
      return call_user_func($default_function, $view, $view_spec, $base_fields);
    }
}

/**
 * Defines the master view.
 */
function __curios_generate_display_master_default(&$view, &$view_spec, $base_fields) {
  $resource = $view_spec->getResource();
  $resource_name = $resource->getMachineName();
  
  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  //$handler->display->display_options['title'] = ''; // No title.
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = FALSE;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'lite';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  
  // No results behavior: Global: Text area.
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'No results';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No results found.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;

  // Relationships.
  foreach ($view_spec->getObjectFields() as $field_id) {
    $field_name = $resource_name.'_'.$field_id;
    $handler->display->display_options['relationships'][$field_name]['id'] = $field_name;
    $handler->display->display_options['relationships'][$field_name]['table'] = $view->base_table;
    $handler->display->display_options['relationships'][$field_name]['field'] = $field_name;
  }

  /* Declare all fields */
  
  // URI field.
  $handler->display->display_options['fields'][$resource_name]['id'] = $resource_name;
  $handler->display->display_options['fields'][$resource_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$resource_name]['field'] = $resource_name;
        
  // Base fields.
  foreach ($base_fields as $field_name) {
    $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
    $handler->display->display_options['fields'][$field_name]['table'] = $view->base_table;
    $handler->display->display_options['fields'][$field_name]['field'] = $field_name;
  }
  
  // Optional data fields.
  foreach ($view_spec->getFieldIds() as $field_id) {
    $field_name = $resource_name.'_'.$field_id;
    $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
    $handler->display->display_options['fields'][$field_name]['table'] = $view->base_table;
    $handler->display->display_options['fields'][$field_name]['field'] = $field_name;
    $handler->display->display_options['fields'][$field_name]['required'] = 0;
  }

  // Global contextual filters.
  __curios_uri_filter($handler, $view, $view_spec);
  __curios_rdf_type_filter($handler, $view, $view_spec);

  return $handler;
}

/**
 * Defines the default summary view.
 *
 * This display shows the title and description of an individual.
 */
function __curios_generate_display_summary_default(&$view, &$view_spec, $base_fields) {
  $config = curios_configuration();
  $resource = $view_spec->getResource();
  $resource_name = $resource->getMachineName();
  $subject_id_field = $resource_name .'_'. $config->getIdentifierFieldId();

  /* Display: Details */
  $handler = $view->new_display('block', 'Summary', 'summary');
  $handler->display->display_options['query']['type'] = 'views_query';
  // Path, menu etc..
  //$handler->display->display_options['path'] = $view_spec->getPath().'/%';

  // Overrides.
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['defaults']['query'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;

  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;

  // Pager options.
  //$handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';

  // Field options.
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 1;

  /* Field: URI */
  $handler->display->display_options['fields'][$resource_name]['id'] = $resource_name;
  $handler->display->display_options['fields'][$resource_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$resource_name]['field'] = $resource_name;
  $handler->display->display_options['fields'][$resource_name]['exclude'] = TRUE;

  // Field: subject id.
  $handler->display->display_options['fields'][$subject_id_field]['id'] = $subject_id_field;
  $handler->display->display_options['fields'][$subject_id_field]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$subject_id_field]['field'] = $subject_id_field;
  $handler->display->display_options['fields'][$subject_id_field]['exclude'] = TRUE;

  // Field: title.
  $handler->display->display_options['fields'][$base_fields['title']]['id'] = $base_fields['title'];
  $handler->display->display_options['fields'][$base_fields['title']]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$base_fields['title']]['field'] = $base_fields['title'];
  $handler->display->display_options['fields'][$base_fields['title']]['label'] = '';
  $handler->display->display_options['fields'][$base_fields['title']]['element_type'] = 'h1';
  $handler->display->display_options['fields'][$base_fields['title']]['required'] = 1;

  // Field: description.
  $handler->display->display_options['fields'][$base_fields['description']]['id'] = $base_fields['description'];
  $handler->display->display_options['fields'][$base_fields['description']]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$base_fields['description']]['field'] = $base_fields['description'];
  $handler->display->display_options['fields'][$base_fields['description']]['label'] = '';
  $handler->display->display_options['fields'][$base_fields['description']]['type'] = 'text_default';
  $handler->display->display_options['fields'][$base_fields['description']]['required'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['exists'] = 0;

  // Field: search link.
  $field_name = 'searchlink';
  $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
  $handler->display->display_options['fields'][$field_name]['table'] = 'views';
  $handler->display->display_options['fields'][$field_name]['field'] = 'nothing';
  $handler->display->display_options['fields'][$field_name]['ui_name'] = 'Search Link';
  $handler->display->display_options['fields'][$field_name]['label'] = '';
  $handler->display->display_options['fields'][$field_name]['alter']['text'] = 'Back to listing';
  $handler->display->display_options['fields'][$field_name]['alter']['make_link'] = 1;
  $handler->display->display_options['fields'][$field_name]['alter']['path'] = $view_spec->getPath().'/';

  
  // Contextual filters.
  __curios_uri_filter($handler, $view, $view_spec);
  __curios_rdf_type_filter($handler, $view, $view_spec);

  return $handler;
}

/**
 * Defines the default properties display view.
 *
 * This display lists all literal fields defined for a browsing class.
 */
function __curios_generate_display_properties_default(&$view, &$view_spec, $base_fields) {
  $config = curios_configuration();
  $resource = $view_spec->getResource();
  $resource_name = $resource->getMachineName();

  // DateRange.
  $date_range_resource = $config->getDateRangeResource();
  $date_range_from_id = $config->getDateRangeFromId();
  $date_range_to_id = $config->getDateRangeToId();

  /* Display: Properties */
  $handler = $view->new_display('block', 'Properties', 'properties');
  $handler->display->display_options['query']['type'] = 'views_query';
  
  // Combine multi-valued fields.
  $handler->display->display_options['query']['options']['consolidate'] = FALSE;

  // Overrides.
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['defaults']['query'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;

  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;

  // Pager options.
  //$handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';

  // Field options.
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 1;

  /* Field: URI */
  $handler->display->display_options['fields'][$resource_name]['id'] = $resource_name;
  $handler->display->display_options['fields'][$resource_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$resource_name]['field'] = $resource_name;
  $handler->display->display_options['fields'][$resource_name]['exclude'] = TRUE;

  // Title field.
  $title_field_name = $resource_name.'_'.$view_spec->getTitleFieldId();
  $field = $config->getField($view_spec->getTitleFieldId());
  $handler->display->display_options['fields'][$title_field_name]['id'] = $title_field_name;
  $handler->display->display_options['fields'][$title_field_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$title_field_name]['field'] = $title_field_name;
  $handler->display->display_options['fields'][$title_field_name]['label'] = __format_name($field->getLabel());
  $handler->display->display_options['fields'][$title_field_name]['element_label_type'] = 'strong';
  $handler->display->display_options['fields'][$title_field_name]['element_label_colon'] = 1;
  $handler->display->display_options['fields'][$title_field_name]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$title_field_name]['hide_empty'] = 1;
  $handler->display->display_options['fields'][$title_field_name]['required'] = 0;

  // Description field.
  $description_field_name = $resource_name.'_'.$view_spec->getDescriptionFieldId();
  $field = $config->getField($view_spec->getDescriptionFieldId());
  $handler->display->display_options['fields'][$description_field_name]['id'] = $description_field_name;
  $handler->display->display_options['fields'][$description_field_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$description_field_name]['field'] = $description_field_name;
  $handler->display->display_options['fields'][$description_field_name]['label'] = __format_name($field->getLabel());
  $handler->display->display_options['fields'][$description_field_name]['exclude'] = TRUE;
  $handler->display->display_options['fields'][$description_field_name]['element_label_type'] = 'strong';
  $handler->display->display_options['fields'][$description_field_name]['element_label_colon'] = 1;
  $handler->display->display_options['fields'][$description_field_name]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$description_field_name]['hide_empty'] = 1;
  $handler->display->display_options['fields'][$description_field_name]['required'] = 0;

  // Field: record type.
  $field_name = "_record_type";
  $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
  $handler->display->display_options['fields'][$field_name]['table'] = 'views';
  $handler->display->display_options['fields'][$field_name]['field'] = 'nothing';
  $handler->display->display_options['fields'][$field_name]['label'] = 'Record Type';
  $handler->display->display_options['fields'][$field_name]['alter']['text'] = $resource->getLabel();
  $handler->display->display_options['fields'][$field_name]['element_label_type'] = 'strong';
  $handler->display->display_options['fields'][$field_name]['element_label_colon'] = 1;
  $handler->display->display_options['fields'][$field_name]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$field_name]['hide_alter_empty'] = 0;

  // Optional data fields.
  $date_range_position = 0;
  foreach ($view_spec->getFieldIds() as $field_id) {
    $field_name = $resource_name.'_'.$field_id;
    $field = $config->getField($field_id);

    // Skip base fields.
    if (in_array($field_name, $base_fields) || $field_name == $title_field_name || $field_name == $description_field_name) {
        continue;
    }
    
    if ($field->getType() == 'daterange') { // date range field.
      // Add relationship.
      $handler->display->display_options['relationships'][$field_name]['id'] = $field_name;
      $handler->display->display_options['relationships'][$field_name]['table'] = $view->base_table;
      $handler->display->display_options['relationships'][$field_name]['field'] = $field_name;
      $handler->display->display_options['relationships'][$field_name]['required'] = 0;

      // DateRange: dateFrom.
      $date_from_field_name = $date_range_resource->getId() .'_'. $date_range_from_id;
      $date_from_views_field = $field_name .'_'. $date_from_field_name;
      $handler->display->display_options['fields'][$date_from_views_field]['id'] =  $date_from_views_field;
      $handler->display->display_options['fields'][$date_from_views_field]['table'] = $view->base_table;
      $handler->display->display_options['fields'][$date_from_views_field]['field'] =  $date_from_field_name;
      $handler->display->display_options['fields'][$date_from_views_field]['relationship'] = $field_name;
      $handler->display->display_options['fields'][$date_from_views_field]['label'] = "$field_id $date_range_from_id";
      $handler->display->display_options['fields'][$date_from_views_field]['exclude'] = TRUE;
      $handler->display->display_options['fields'][$date_from_views_field]['required'] = 1;

      // DateRange: dateTo.
      $date_to_field_name = $date_range_resource->getId() .'_'. $date_range_to_id;
      $date_to_views_field = $field_name .'_'. $date_to_field_name;
      $handler->display->display_options['fields'][$date_to_views_field]['id'] =  $date_to_views_field;
      $handler->display->display_options['fields'][$date_to_views_field]['table'] = $view->base_table;
      $handler->display->display_options['fields'][$date_to_views_field]['field'] =  $date_to_field_name;
      $handler->display->display_options['fields'][$date_to_views_field]['relationship'] = $field_name;
      $handler->display->display_options['fields'][$date_to_views_field]['label'] = "$field_id $date_range_to_id";
      $handler->display->display_options['fields'][$date_to_views_field]['exclude'] = TRUE;
      $handler->display->display_options['fields'][$date_to_views_field]['required'] = 1;

      // Date range renderer.
      $date_range_views_field = $field_name .'_date_range';
      $handler->display->display_options['fields'][$date_range_views_field]['id'] = $date_range_views_field;
      $handler->display->display_options['fields'][$date_range_views_field]['table'] = 'views';
      $handler->display->display_options['fields'][$date_range_views_field]['field'] = 'curios_date_range_field';
      $handler->display->display_options['fields'][$date_range_views_field]['label'] = __format_name($field->getLabel());
      $handler->display->display_options['fields'][$date_range_views_field]['element_label_type'] = 'strong';
      $handler->display->display_options['fields'][$date_range_views_field]['element_label_colon'] = 1;
      $handler->display->display_options['fields'][$date_range_views_field]['element_default_classes'] = 1;
      $handler->display->display_options['fields'][$date_range_views_field]['hide_empty'] = 1;
      $handler->display->display_options['fields'][$date_range_views_field]['exclude'] = FALSE;
      $handler->display->display_options['fields'][$date_range_views_field]['required'] = 1;
      $handler->display->display_options['fields'][$date_range_views_field]['date_range_position'] = $date_range_position;
      $handler->display->display_options['fields'][$date_range_views_field]['date_range_from'] = $date_from_field_name;
      $handler->display->display_options['fields'][$date_range_views_field]['date_range_to'] = $date_to_field_name;

      // Track number of date ranges added to the field set.
      $date_range_position += 1;
      
    } else { // Text field / default.
      $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
      $handler->display->display_options['fields'][$field_name]['table'] = $view->base_table;
      $handler->display->display_options['fields'][$field_name]['field'] = $field_name;
      $handler->display->display_options['fields'][$field_name]['label'] = __format_name($field->getLabel());
      $handler->display->display_options['fields'][$field_name]['element_label_type'] = 'strong';
      $handler->display->display_options['fields'][$field_name]['element_label_colon'] = 1;
      $handler->display->display_options['fields'][$field_name]['element_default_classes'] = 1;
      $handler->display->display_options['fields'][$field_name]['hide_empty'] = 1;
      $handler->display->display_options['fields'][$field_name]['required'] = 0;
    }
  }

  // Contextual filters.
  __curios_uri_filter($handler, $view, $view_spec);
  __curios_rdf_type_filter($handler, $view, $view_spec);

  return $handler;
}

/**
 * Generates a relationships block.
 *
 * This display lists links to pages for other records in the system.
 */
function __curios_generate_object_block(&$view, &$view_spec, $base_fields, $field_id) {
  $config = curios_configuration();
  $resource = $view_spec->getResource();
  $resource_name = $resource->getMachineName();

  $ranges = $resource->getObjectFieldRanges();
  $field = $config->getField($field_id);
  $field_name = $resource_name.'_'.$field_id;

  // Default.
  $use_rewrite = FALSE;

  // Find target type.
  if (empty($ranges[$field_id])) {
    // No target, default to hc_subject.
    $ranges[$field_id] = $config->getDefaultResourceId();
  } else if (is_array($ranges[$field_id])) {
    // Non-empty array -> multiple targets.
    $ranges[$field_id] = $config->getDefaultResourceId();
    $use_rewrite = TRUE;
  } // else -> single target.

  $handler = $view->new_display('block', 'Rel: '.$field->getLabel(), 'object_'.$field_name);


  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['options']['offset'] = '0';
  // FIXME using rdf:type increases the results, ARC2 dies, limit to 100 for now.
  $handler->display->display_options['pager']['type'] = 'none';
  //$handler->display->display_options['pager']['type'] = 'lite';
  //$handler->display->display_options['pager']['options']['items_per_page'] = '100';
  
  // Indicates whether the pre_render hook should attempt to rewrite the link target.
  $handler->display->display_options['curios']['rewrite_object_target'] = $use_rewrite;

  $handler->display->display_options['title'] = __format_name($field->getLabel());

  // CURIOS specific options...
  $handler->display->display_options['curios']['display_type'] = 'object_block';

  // Overrides.
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = TRUE;
    
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';

  $handler->display->display_options['row_options']['hide_empty'] = 1;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;

  $handler->display->display_options['query']['options']['consolidate'] = FALSE;

  // Relationship.
  $handler->display->display_options['relationships'][$field_name]['id'] = $field_name;
  $handler->display->display_options['relationships'][$field_name]['table'] = $view->base_table;
  $handler->display->display_options['relationships'][$field_name]['field'] = $field_name;
  $handler->display->display_options['relationships'][$field_name]['required'] = 0;

  $title_field_name = $ranges[$field_id].'_'.$config->getTitleFieldId();
  $identifier_field_name = $ranges[$field_id].'_'.$config->getIdentifierFieldId();
  $type_field_name = $ranges[$field_id].'_type';
  $description_field_name = $ranges[$field_id].'_'.$config->getDescriptionFieldId();
  $target_view_id = $config->getViewIdForResource($ranges[$field_id]);
  $target_view = $config->getViewSpec($target_view_id);

  // Identifier.
  $handler->display->display_options['fields'][$identifier_field_name]['id'] = $identifier_field_name;
  $handler->display->display_options['fields'][$identifier_field_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$identifier_field_name]['field'] = $identifier_field_name;
  $handler->display->display_options['fields'][$identifier_field_name]['relationship'] = $field_name;
  $handler->display->display_options['fields'][$identifier_field_name]['label'] = '';
  $handler->display->display_options['fields'][$identifier_field_name]['exclude'] = TRUE;
  $handler->display->display_options['fields'][$identifier_field_name]['required'] = 1;

  
 
  if (!$use_rewrite) {
    // Display the title field directly (no rewriting).
    $handler->display->display_options['fields'][$title_field_name]['id'] =  $title_field_name;
    $handler->display->display_options['fields'][$title_field_name]['table'] = $view->base_table;
    $handler->display->display_options['fields'][$title_field_name]['field'] =  $title_field_name;
    $handler->display->display_options['fields'][$title_field_name]['relationship'] = $field_name;
    $handler->display->display_options['fields'][$title_field_name]['label'] = '';
    $handler->display->display_options['fields'][$title_field_name]['alter']['alter_text'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['make_link'] = 1;
    $handler->display->display_options['fields'][$title_field_name]['alter']['path'] = $target_view->getPath().'/['.$identifier_field_name.']';
    $handler->display->display_options['fields'][$title_field_name]['alter']['max_length'] = '15';
    $handler->display->display_options['fields'][$title_field_name]['alter']['word_boundary'] = FALSE;
    $handler->display->display_options['fields'][$title_field_name]['alter']['trim'] = TRUE;
    $handler->display->display_options['fields'][$title_field_name]['hide_empty'] = 1;
    $handler->display->display_options['fields'][$title_field_name]['required'] = 1;
  } else {// Set type and rewrite field and hidden title field for rewriter.
    $handler->display->display_options['fields'][$title_field_name]['id'] =  $title_field_name;
    $handler->display->display_options['fields'][$title_field_name]['table'] = $view->base_table;
    $handler->display->display_options['fields'][$title_field_name]['field'] =  $title_field_name;
    $handler->display->display_options['fields'][$title_field_name]['relationship'] = $field_name;
    $handler->display->display_options['fields'][$title_field_name]['label'] = '';
    $handler->display->display_options['fields'][$title_field_name]['exclude'] = TRUE;
    $handler->display->display_options['fields'][$title_field_name]['required'] = 1;

    $handler->display->display_options['fields'][$type_field_name]['id'] =  $type_field_name;
    $handler->display->display_options['fields'][$type_field_name]['table'] = $view->base_table;
    $handler->display->display_options['fields'][$type_field_name]['field'] =  $type_field_name;
    $handler->display->display_options['fields'][$type_field_name]['relationship'] = $field_name;
    $handler->display->display_options['fields'][$type_field_name]['label'] = '';
    $handler->display->display_options['fields'][$type_field_name]['exclude'] = TRUE;
    $handler->display->display_options['fields'][$type_field_name]['required'] = 1;

    $handler->display->display_options['fields'][$description_field_name]['id'] = $description_field_name;
    $handler->display->display_options['fields'][$description_field_name]['table'] = $view->base_table;
    $handler->display->display_options['fields'][$description_field_name]['field'] = $description_field_name;
    $handler->display->display_options['fields'][$description_field_name]['relationship'] = $field_name;
    $handler->display->display_options['fields'][$description_field_name]['label'] = '';
    $handler->display->display_options['fields'][$description_field_name]['exclude'] = TRUE;
    $handler->display->display_options['fields'][$description_field_name]['type'] = 'text_trimmed';
    $handler->display->display_options['fields'][$description_field_name]['required'] = 0;
    $handler->display->display_options['fields'][$description_field_name]['exists'] = 0;
    $handler->display->display_options['fields'][$description_field_name]['settings'] = array(
   'trim_length' => '150',
  );

    /* Field: Global: Link Target Rewriter */
    $title_field_id = $config->getDefaultResourceId().'_'.$config->getTitleFieldId();
    $identifier_field_id = $config->getDefaultResourceId().'_'.$config->getIdentifierFieldId();
    $description_field_id = $config->getDefaultResourceId().'_'.$config->getDescriptionFieldId();
    $default_view_spec = $config->getViewSpec($config->getViewIdForResource($config->getDefaultResourceId()));
    $default_view_path = $default_view_spec->getPath();
    
    $handler->display->display_options['fields']['curios_link_target_rewriter']['id'] = 'curios_link_target_rewriter';
    $handler->display->display_options['fields']['curios_link_target_rewriter']['table'] = 'views';
    $handler->display->display_options['fields']['curios_link_target_rewriter']['field'] = 'curios_link_target_rewriter';
    $handler->display->display_options['fields']['curios_link_target_rewriter']['label'] = '';
    $handler->display->display_options['fields']['curios_link_target_rewriter']['alter']['alter_text'] = TRUE;
    $handler->display->display_options['fields']['curios_link_target_rewriter']['alter']['text'] = "[$title_field_id]";
    $handler->display->display_options['fields']['curios_link_target_rewriter']['alter']['make_link'] = TRUE;
    $handler->display->display_options['fields']['curios_link_target_rewriter']['alter']['path'] = "$default_view_path/[$identifier_field_id]";
    $handler->display->display_options['fields']['curios_link_target_rewriter']['alter']['alt'] = "[$description_field_id]";
    $handler->display->display_options['fields']['curios_link_target_rewriter']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['curios_link_target_rewriter']['hide_alter_empty'] = FALSE;
    $handler->display->display_options['fields']['curios_link_target_rewriter']['alter']['max_length'] = '35';
    $handler->display->display_options['fields']['curios_link_target_rewriter']['alter']['word_boundary'] = TRUE;
    $handler->display->display_options['fields']['curios_link_target_rewriter']['alter']['trim'] = TRUE;
      
 }
  // Contextual filters.
  __curios_uri_filter($handler, $view, $view_spec);
  __curios_rdf_type_filter($handler, $view, $view_spec);

  return TRUE;
}

/**
 * Generates the default listings page view.
 */
function __curios_generate_display_listing_default(&$view, &$view_spec, $base_fields) {
  $config = curios_configuration();
  $resource = $view_spec->getResource();
  $resource_name = $resource->getMachineName();
  $image_file = $resource_name.'_'.$config->getImageRelationshipFieldId();
  $subject_id_field = $resource_name.'_'.$config->getIdentifierFieldId();
  $published_field = $resource_name.'_'.$config->getPublishedFieldId();
  
  $handler = $view->new_display('block', 'Listing', 'listing');
  
  // Path, menu etc.
  $handler->display->display_options['title'] = $view_spec->getLabel();
  
  // Overrides.
  $handler->display->display_options['defaults']['fields'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;

  // Pager options.
  $handler->display->display_options['pager']['type'] = 'lite';
  $handler->display->display_options['pager']['options']['items_per_page'] = '15';
  $handler->display->display_options['pager']['options']['offset'] = '';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '15, 30, 50';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  
  // Table options.
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    $resource_name => $resource_name,
    $base_fields['title'] => $base_fields['title'],
    $base_fields['description'] => $base_fields['description'],
    $published_field => $published_field,
    $image_file => $image_file,
    'subject_id_rewrite' => 'subject_id_rewrite',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    $resource_name => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    $base_fields['title'] => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    $base_fields['description'] => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
   $published_field => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    $image_file => array(
     'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
    ),
    'subject_id_rewrite' => array(
      'align' => 'views-align-right',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  
  // Header: page description area.
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = $view_spec->getPageDescription();
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  $handler->display->display_options['header']['area']['tokenize'] = 0;
  
  // Field: URI.
  $handler->display->display_options['fields'][$resource_name]['id'] = $resource_name;
  $handler->display->display_options['fields'][$resource_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$resource_name]['field'] = $resource_name;
  $handler->display->display_options['fields'][$resource_name]['exclude'] = TRUE;
 
  // Field: subject id.
  $handler->display->display_options['fields'][$subject_id_field]['id'] = $subject_id_field;
  $handler->display->display_options['fields'][$subject_id_field]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$subject_id_field]['field'] = $subject_id_field;
  $handler->display->display_options['fields'][$subject_id_field]['exclude'] = TRUE;
  
  // Field: title.
  $handler->display->display_options['fields'][$base_fields['title']]['id'] = $base_fields['title'];
  $handler->display->display_options['fields'][$base_fields['title']]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$base_fields['title']]['field'] = $base_fields['title'];
  $handler->display->display_options['fields'][$base_fields['title']]['label'] = 'Title';
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['alter_text'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['make_link'] = 1;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['path'] = $view_spec->getPath().'/['.$subject_id_field.']';
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['target'] = '_blank';
  $handler->display->display_options['fields'][$base_fields['title']]['element_label_colon'] = 1;
  $handler->display->display_options['fields'][$base_fields['title']]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$base_fields['title']]['required'] = 1;
  
  // Field: description.
  $handler->display->display_options['fields'][$base_fields['description']]['id'] = $base_fields['description'];
  $handler->display->display_options['fields'][$base_fields['description']]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$base_fields['description']]['field'] = $base_fields['description'];
  $handler->display->display_options['fields'][$base_fields['description']]['label'] = 'Description';
  $handler->display->display_options['fields'][$base_fields['description']]['type'] = 'text_default';
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['trim'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['max_length'] = '220';
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['strip_tags'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['html'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['element_label_colon'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['required'] = 0;


  /* Field: Published */
 $handler->display->display_options['fields'][$published_field]['id'] = $published_field;
 $handler->display->display_options['fields'][$published_field]['table'] = $view->base_table;
 $handler->display->display_options['fields'][$published_field]['field'] = $published_field;
 $handler->display->display_options['fields'][$published_field]['alter']['url_encode'] = 0;
 $handler->display->display_options['fields'][$published_field]['required'] = 0;
 $handler->display->display_options['fields'][$published_field]['exists'] = 0;
 $handler->display->display_options['fields'][$published_field]['exclude'] = TRUE;


  /* Field: HasFile */
  $handler->display->display_options['fields'][$image_file]['id'] = $image_file;
  $handler->display->display_options['fields'][$image_file]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$image_file]['field'] = $image_file;
  $handler->display->display_options['fields'][$image_file]['label'] = 'Images';
  $handler->display->display_options['fields'][$image_file]['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields'][$image_file]['alter']['text'] = 'Yes';
  $handler->display->display_options['fields'][$image_file]['alter']['url_encode'] = 0;
  $handler->display->display_options['fields'][$image_file]['element_type'] = 'span';
  $handler->display->display_options['fields'][$image_file]['element_class'] = "listing-image-[$image_file]";
  $handler->display->display_options['fields'][$image_file]['required'] = 0;
  $handler->display->display_options['fields'][$image_file]['exists'] = 1;

  $handler->display->display_options['fields']['subject_id_rewrite']['id'] = 'subject_id_rewrite';
  $handler->display->display_options['fields']['subject_id_rewrite']['table'] = 'views';
  $handler->display->display_options['fields']['subject_id_rewrite']['field'] = 'nothing';
  $handler->display->display_options['fields']['subject_id_rewrite']['label'] = 'Id';
  $handler->display->display_options['fields']['subject_id_rewrite']['alter']['text'] = '['.$subject_id_field.']';
 
  // Contextual filters.
  __curios_rdf_type_filter($handler, $view, $view_spec);
 
 /* Filter: Published */
 $handler->display->display_options['filters'][$published_field]['id'] = $published_field;
 $handler->display->display_options['filters'][$published_field]['table'] = $view->base_table;
 $handler->display->display_options['filters'][$published_field]['field'] = $published_field;
 $handler->display->display_options['filters'][$published_field]['operator'] = '~=';
 $handler->display->display_options['filters'][$published_field]['value'] = 'yes';
 $handler->display->display_options['filters'][$published_field]['sparql_options'] = array(
    'value_type' => 'string',
    'language' => '0',
  );
  // Exposed filter: title.
  $handler->display->display_options['filters'][$base_fields['title']]['id'] = $base_fields['title'];
  $handler->display->display_options['filters'][$base_fields['title']]['table'] = $view->base_table;
  $handler->display->display_options['filters'][$base_fields['title']]['field'] = $base_fields['title'];
  $handler->display->display_options['filters'][$base_fields['title']]['operator'] = 'search';
  $handler->display->display_options['filters'][$base_fields['title']]['exposed'] = TRUE;
  $handler->display->display_options['filters'][$base_fields['title']]['expose']['operator_id'] = $base_fields['title'].'_op';
  $handler->display->display_options['filters'][$base_fields['title']]['expose']['label'] = 'Search '.$view_spec->getLabel();
  $handler->display->display_options['filters'][$base_fields['title']]['expose']['operator'] = $base_fields['title'].'_op';
  $handler->display->display_options['filters'][$base_fields['title']]['expose']['identifier'] = 'name';
  $handler->display->display_options['filters'][$base_fields['title']]['expose']['required'] = 0;
  $handler->display->display_options['filters'][$base_fields['title']]['expose']['multiple'] = FALSE;
  $handler->display->display_options['filters'][$base_fields['title']]['sparql_options'] = array(
    'value_type' => 'string',
    'language' => '0',
  );

  // TODO types are no longer classes in the ontology, this needs to be updated to dynamically read typeOf properties.
  // Exposed filter: rdf:type.
  /*
  $sub_types = $resource->getSubTypes();
  if (!empty($sub_types)) {
    $type_field_name = $resource_name.'_type';
    $handler->display->display_options['filters'][$type_field_name]['id'] = $type_field_name;
    $handler->display->display_options['filters'][$type_field_name]['table'] = $view->base_table;
    $handler->display->display_options['filters'][$type_field_name]['field'] = $type_field_name;
    $handler->display->display_options['filters'][$type_field_name]['exposed'] = TRUE;
    $handler->display->display_options['filters'][$type_field_name]['expose']['operator_id'] = $type_field_name.'_op';
    $handler->display->display_options['filters'][$type_field_name]['expose']['label'] = 'Type';
    $handler->display->display_options['filters'][$type_field_name]['expose']['operator'] = $type_field_name.'_op';
    $handler->display->display_options['filters'][$type_field_name]['expose']['identifier'] = $type_field_name;
    $handler->display->display_options['filters'][$type_field_name]['expose']['reduce'] = 1;
    $handler->display->display_options['filters'][$type_field_name]['is_grouped'] = TRUE;
    $handler->display->display_options['filters'][$type_field_name]['group_info']['label'] = 'Filter';
    $handler->display->display_options['filters'][$type_field_name]['group_info']['identifier'] = 'type';
    $handler->display->display_options['filters'][$type_field_name]['group_info']['remember'] = 1;
    $handler->display->display_options['filters'][$type_field_name]['group_info']['group_items'] = array();
    foreach ($sub_types as $label => $type) {
      $handler->display->display_options['filters'][$type_field_name]['group_info']['group_items'][] =
          array('title' => __format_name($label), 'value' => $type, 'operator' => '=');
    }
  }
  */

  return $handler;
}

/**
 * Generates the default image gallery view.
 */
function __curios_generate_display_images_default(&$view, &$view_spec, $base_fields) {
  $config = curios_configuration();
  $resource = $view_spec->getResource();
  $resource_name = $resource->getMachineName();
  $subject_id_field = $resource_name.'_'.$config->getIdentifierFieldId();
  $image_view_id = $config->getViewIdForResource($config->getImageResourceId());
  $image_view_spec = $config->getViewSpec($image_view_id);

  /* Display: Images */
  $handler = $view->new_display('block', 'Images', 'images');
  
  $handler->display->display_options['pager']['type'] = 'lite';
  $handler->display->display_options['attachment_position'] = 'after';
    $handler->display->display_options['displays'] = array(
      'details' => 'details',
      'default' => 0,
      'page' => 0,
  );
  
  // Overrides.
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = TRUE;
  
  
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  
  $handler->display->display_options['row_options']['hide_empty'] = 1;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;

  // Relationship
  $relationship_field = $resource_name.'_'.$config->getImageRelationshipFieldId();
  $handler->display->display_options['relationships'][$relationship_field]['id'] = $relationship_field;
  $handler->display->display_options['relationships'][$relationship_field]['table'] = $view->base_table;
  $handler->display->display_options['relationships'][$relationship_field]['field'] = $relationship_field;
  $handler->display->display_options['relationships'][$relationship_field]['required'] = 0;

  // Field: subject id.
  $handler->display->display_options['fields'][$subject_id_field]['id'] = $subject_id_field;
  $handler->display->display_options['fields'][$subject_id_field]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$subject_id_field]['field'] = $subject_id_field;
  $handler->display->display_options['fields'][$subject_id_field]['relationship'] = $relationship_field;
  $handler->display->display_options['fields'][$subject_id_field]['exclude'] = TRUE;

  // Field: file.
  $field_name = $config->getImageResourceId().'_'.$config->getURLFieldId();
  $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
  $handler->display->display_options['fields'][$field_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$field_name]['field'] = $field_name;
  $handler->display->display_options['fields'][$field_name]['relationship'] = $relationship_field;
  $handler->display->display_options['fields'][$field_name]['label'] = '';
  $handler->display->display_options['fields'][$field_name]['exclude'] = TRUE;
  $handler->display->display_options['fields'][$field_name]['required'] = 1;
  
  // Field: title
  $handler->display->display_options['fields'][$base_fields['title']]['id'] = $base_fields['title'];
  $handler->display->display_options['fields'][$base_fields['title']]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$base_fields['title']]['field'] = $base_fields['title'];
  $handler->display->display_options['fields'][$base_fields['title']]['relationship'] = $relationship_field;
  $handler->display->display_options['fields'][$base_fields['title']]['label'] = '';
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['alter_text'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['make_link'] = 1;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['path'] = $image_view_spec->getPath().'/['.$subject_id_field.']';
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['trim'] = 1;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['max_length'] = '40';
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields'][$base_fields['title']]['required'] = 1;

  // Rewrite URL and output html.
  $handler->display->display_options['fields']['curios_link_target_rewriter']['id'] = 'curios_image_thumbnail_field';
  $handler->display->display_options['fields']['curios_link_target_rewriter']['table'] = 'views';
  $handler->display->display_options['fields']['curios_link_target_rewriter']['field'] = 'curios_image_thumbnail_field';
  $handler->display->display_options['fields']['curios_link_target_rewriter']['label'] = '';
  $handler->display->display_options['fields']['curios_link_target_rewriter']['alter']['text'] = "[$field_name]";
  $handler->display->display_options['fields']['curios_link_target_rewriter']['alter']['make_link'] = FALSE;
  $handler->display->display_options['fields']['curios_link_target_rewriter']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['curios_link_target_rewriter']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['curios_link_target_rewriter']['title_field'] = $base_fields['title'];
  $handler->display->display_options['fields']['curios_link_target_rewriter']['id_field'] = $subject_id_field;
  $handler->display->display_options['fields']['curios_link_target_rewriter']['view_path'] = $image_view_spec->getPath();
  
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = '&nbsp;';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;

  __curios_uri_filter($handler, $view, $view_spec);
  __curios_rdf_type_filter($handler, $view, $view_spec);

  return $handler;
}

/**
 * Filters a view by OWL class.
 */
function __curios_rdf_type_filter(&$handler, $view, $view_spec) {
  $resource_name = $view_spec->getResource()->getMachineName();
  $field_name = $resource_name.'_type';
  $handler->display->display_options['arguments'][$field_name]['id'] = $field_name;
  $handler->display->display_options['arguments'][$field_name]['table'] = $view->base_table;
  $handler->display->display_options['arguments'][$field_name]['field'] = $field_name;
  $handler->display->display_options['arguments'][$field_name]['default_action'] = 'default';
  $handler->display->display_options['arguments'][$field_name]['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments'][$field_name]['default_argument_options']['argument'] = 'no value';
  $handler->display->display_options['arguments'][$field_name]['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments'][$field_name]['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments'][$field_name]['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments'][$field_name]['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments'][$field_name]['sparql_options'] = array(
    'value_type' => 'uri',
    'language' => '0',
    'code' => 'return \''.$view_spec->getResource()->getRDFType().'\';',
  );
}

/**
 * Generates display with admin links for users with 'curios manage repository' access.
 */
function __curios_generate_display_admin_tools_default(&$view, &$view_spec, $base_fields) {
  $config = curios_configuration();
  $resource = $view_spec->getResource();
  $resource_name = $resource->getMachineName();
  $subject_id_field = $resource_name.'_'.$config->getIdentifierFieldId();
  $admin_edit_path = 'curios/manage/edit/'. $resource_name;

  /* Display: Details */
  $handler = $view->new_display('block', 'Admin Tools', 'admin_tools');
  $handler->display->display_options['query']['type'] = 'views_query';

  // Overrides.
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['defaults']['query'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;

  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;

  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'curios manage repository';

  $handler->display->display_options['pager']['type'] = 'none';

  // Field options.
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 1;

  /* Field: URI */
  $handler->display->display_options['fields'][$resource_name]['id'] = $resource_name;
  $handler->display->display_options['fields'][$resource_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$resource_name]['field'] = $resource_name;
  $handler->display->display_options['fields'][$resource_name]['exclude'] = TRUE;

  // Field: subject id.
  $handler->display->display_options['fields'][$subject_id_field]['id'] = $subject_id_field;
  $handler->display->display_options['fields'][$subject_id_field]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$subject_id_field]['field'] = $subject_id_field;
  $handler->display->display_options['fields'][$subject_id_field]['exclude'] = TRUE;

  // Edit record button.
  if ($resource_name != $config->getDefaultResourceId()) { // Do not display edit option for the default resource/class.
    $field_name = 'curios_admin_edit_link';
    $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
    $handler->display->display_options['fields'][$field_name]['table'] = 'views';
    $handler->display->display_options['fields'][$field_name]['field'] = 'nothing';
    $handler->display->display_options['fields'][$field_name]['label'] = '';
    $handler->display->display_options['fields'][$field_name]['alter']['text'] = '[ Edit This Record ]';
    $handler->display->display_options['fields'][$field_name]['ui_name'] = 'Edit Record Link';
    $handler->display->display_options['fields'][$field_name]['alter']['alter_text'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['make_link'] = 1;
    $handler->display->display_options['fields'][$field_name]['alter']['path'] = $admin_edit_path.'/['.$subject_id_field.']';
  }
  // Field: update link to trigger recomputation of inferences
  $field_name = 'updatelink';
  $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
  $handler->display->display_options['fields'][$field_name]['table'] = 'views';
  $handler->display->display_options['fields'][$field_name]['field'] = 'nothing';
  $handler->display->display_options['fields'][$field_name]['ui_name'] = 'Update record';
  $handler->display->display_options['fields'][$field_name]['label'] = '';
  $handler->display->display_options['fields'][$field_name]['alter']['text'] = '[ Update all relationships ]';
  $handler->display->display_options['fields'][$field_name]['alter']['alter_text'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['make_link'] = 1;
  $handler->display->display_options['fields'][$field_name]['element_wrapper_class'] = 'views-field-curios-admin-edit-link';
  $handler->display->display_options['fields'][$field_name]['alter']['path'] = 'curios/manage/recompute-inferences/'.$view_spec->getPath()."/[$subject_id_field]";


  // Contextual filters.
  __curios_uri_filter($handler, $view, $view_spec);
  __curios_rdf_type_filter($handler, $view, $view_spec);

  return $handler;
}

/**
 * Defines the default view for retrieving record metadata.
 */
function __curios_generate_display_record_meta_default(&$view, &$view_spec, $base_fields) {
  $config = curios_configuration();
  $resource = $view_spec->getResource();
  $resource_name = $resource->getId();

  /* Display: Properties */
  $handler = $view->new_display('block', 'Record Meta', 'record-meta');
  $handler->display->display_options['query']['type'] = 'views_query';

  // Combine multi-valued fields.
  $handler->display->display_options['query']['options']['consolidate'] = FALSE;

  // Overrides.
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['defaults']['query'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;

  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;

  // Pager options.
  $handler->display->display_options['pager']['type'] = 'none';

  // Field options.
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 1;

  /* Field: URI */
  $handler->display->display_options['fields'][$resource_name]['id'] = $resource_name;
  $handler->display->display_options['fields'][$resource_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$resource_name]['field'] = $resource_name;
  $handler->display->display_options['fields'][$resource_name]['exclude'] = FALSE;
  $handler->display->display_options['fields'][$resource_name]['hide_empty'] = 0;
  $handler->display->display_options['fields'][$resource_name]['empty_zero'] = 0;
  $handler->display->display_options['fields'][$resource_name]['hide_alter_empty'] = 0;

  // Owner field.
  $owner_field_name = $resource_name.'_'.$config->getOwnerFieldId();
  $owner_field = $config->getField($config->getOwnerFieldId());
  $handler->display->display_options['fields'][$owner_field_name]['id'] = $owner_field_name;
  $handler->display->display_options['fields'][$owner_field_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$owner_field_name]['field'] = $owner_field_name;
  $handler->display->display_options['fields'][$owner_field_name]['label'] = __format_name($owner_field->getLabel());
  $handler->display->display_options['fields'][$owner_field_name]['element_label_type'] = 'strong';
  $handler->display->display_options['fields'][$owner_field_name]['element_label_colon'] = 1;
  $handler->display->display_options['fields'][$owner_field_name]['hide_empty'] = 1;
  $handler->display->display_options['fields'][$owner_field_name]['required'] = 0;

  // Maintainer field.
  $maintainer_field_name = $resource_name.'_'.$config->getMaintainerFieldId();
  $maintainer_field = $config->getField($config->getMaintainerFieldId());
  $handler->display->display_options['fields'][$maintainer_field_name]['id'] = $maintainer_field_name;
  $handler->display->display_options['fields'][$maintainer_field_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$maintainer_field_name]['field'] = $maintainer_field_name;
  $handler->display->display_options['fields'][$maintainer_field_name]['label'] = __format_name($maintainer_field->getLabel());
  $handler->display->display_options['fields'][$maintainer_field_name]['element_label_type'] = 'strong';
  $handler->display->display_options['fields'][$maintainer_field_name]['element_label_colon'] = 1;
  $handler->display->display_options['fields'][$maintainer_field_name]['hide_empty'] = 1;
  $handler->display->display_options['fields'][$maintainer_field_name]['required'] = 0;

  // Published field.
  $published_field_name = $resource_name.'_'.$config->getpublishedFieldId();
  $published_field = $config->getField($config->getpublishedFieldId());
  $handler->display->display_options['fields'][$published_field_name]['id'] = $published_field_name;
  $handler->display->display_options['fields'][$published_field_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$published_field_name]['field'] = $published_field_name;
  $handler->display->display_options['fields'][$published_field_name]['label'] = __format_name($published_field->getLabel());
  $handler->display->display_options['fields'][$published_field_name]['element_label_type'] = 'strong';
  $handler->display->display_options['fields'][$published_field_name]['element_label_colon'] = 1;
  $handler->display->display_options['fields'][$published_field_name]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$published_field_name]['hide_empty'] = 1;
  $handler->display->display_options['fields'][$published_field_name]['required'] = 0;

  // editor notes
  $editor_notes_field_name = $resource_name.'_'.$config->getEditorNotesFieldId();
  $editor_notes_field = $config->getField($config->getEditorNotesFieldId());
  $handler->display->display_options['fields'][$editor_notes_field_name]['id'] = $editor_notes_field_name;
  $handler->display->display_options['fields'][$editor_notes_field_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$editor_notes_field_name]['field'] = $editor_notes_field_name;
  $handler->display->display_options['fields'][$editor_notes_field_name]['label'] = __format_name($editor_notes_field->getLabel());
  $handler->display->display_options['fields'][$editor_notes_field_name]['element_label_type'] = 'strong';
  $handler->display->display_options['fields'][$editor_notes_field_name]['element_label_colon'] = 1;
  $handler->display->display_options['fields'][$editor_notes_field_name]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$editor_notes_field_name]['hide_empty'] = 1;
  $handler->display->display_options['fields'][$editor_notes_field_name]['required'] = 0;

  // Contextual filters.
  __curios_uri_filter($handler, $view, $view_spec);
  __curios_rdf_type_filter($handler, $view, $view_spec);

  return $handler;
}


/**
 * Generates the default pending-record page view.
 */
function __curios_generate_display_pending_records_default(&$view, &$view_spec, $base_fields) {
  $config = curios_configuration();
  $resource = $view_spec->getResource();
  $resource_name = $resource->getMachineName();
  $image_file = $resource_name.'_'.$config->getImageRelationshipFieldId();
  $subject_id_field = $resource_name.'_'.$config->getIdentifierFieldId();
  $base_fields = array(
    'title'       => $resource_name.'_'.$config->getTitleFieldId(),
    'description' => $resource_name.'_'.$config->getDescriptionFieldId(),
    'published' =>   $resource_name.'_'.$config->getPublishedFieldId(),
    'maintainers' => $resource_name.'_'.$config->getMaintainerFieldId(),
    'owner' => $resource_name.'_'.$config->getOwnerFieldId(),
);

/* Display: pending-records */
$handler = $view->new_display('page', 'Pending Records', 'page');
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['path'] = 'pending-records/'.$view_spec->getPath();
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = $view_spec->getLabel();
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['name'] = 'menu-pending';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'curios view pending records';

$handler->display->display_options['query']['options']['consolidate'] = TRUE;
  
  // Path, menu etc.
  $handler->display->display_options['title'] = $view_spec->getLabel(). ' Pending Records';
  
  // Overrides.
  $handler->display->display_options['defaults']['fields'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;

  // Pager options.
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  

  // Table options.
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    $resource_name => $resource_name,
    $subject_id_field => $subject_id_field,
    $base_fields['title'] => $base_fields['title'],
    $base_fields['description'] => $base_fields['description'],
    $base_fields['published'] => $base_fields['published'],
    $base_fields['maintainers'] =>     $base_fields['maintainers'],
    $base_fields['owner'] =>     $base_fields['owner'],

    'subject_id_rewrite' => 'subject_id_rewrite',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    $resource_name => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),

$subject_id_field  => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    $base_fields['title'] => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    $base_fields['description'] => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    $base_fields['published'] => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    $base_fields['maintainers'] => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    $base_fields['owner'] => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'subject_id_rewrite' => array(
      'align' => 'views-align-right',
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'separator' => '',
      'empty_column' => 0,
    ),
 
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  
  // Field: URI.
  $handler->display->display_options['fields'][$resource_name]['id'] = $resource_name;
  $handler->display->display_options['fields'][$resource_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$resource_name]['field'] = $resource_name;
  $handler->display->display_options['fields'][$resource_name]['exclude'] = TRUE;
 
  // Field: subject id.
  $handler->display->display_options['fields'][$subject_id_field]['id'] = $subject_id_field;
  $handler->display->display_options['fields'][$subject_id_field]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$subject_id_field]['field'] = $subject_id_field;
 // $handler->display->display_options['fields'][$subject_id_field]['exclude'] = TRUE;
  
  // Field: title.
  $handler->display->display_options['fields'][$base_fields['title']]['id'] = $base_fields['title'];
  $handler->display->display_options['fields'][$base_fields['title']]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$base_fields['title']]['field'] = $base_fields['title'];
  $handler->display->display_options['fields'][$base_fields['title']]['label'] = 'Title';
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['alter_text'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['make_link'] = 1;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['path'] = $view_spec->getPath().'/['.$subject_id_field.']';
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['target'] = '_blank';
  $handler->display->display_options['fields'][$base_fields['title']]['element_label_colon'] = 1;
  $handler->display->display_options['fields'][$base_fields['title']]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$base_fields['title']]['required'] = 1;
  
  // Field: description.
  $handler->display->display_options['fields'][$base_fields['description']]['id'] = $base_fields['description'];
  $handler->display->display_options['fields'][$base_fields['description']]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$base_fields['description']]['field'] = $base_fields['description'];
  $handler->display->display_options['fields'][$base_fields['description']]['label'] = 'Description';
  $handler->display->display_options['fields'][$base_fields['description']]['type'] = 'text_default';
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['trim'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['max_length'] = '220';
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['strip_tags'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['html'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['element_label_colon'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['required'] = 0;

/* Field: Published */
$handler->display->display_options['fields'][$base_fields['published']]['id'] = $base_fields['published'];
$handler->display->display_options['fields'][$base_fields['published']]['table'] = $view->base_table;
$handler->display->display_options['fields'][$base_fields['published']]['field'] = $base_fields['published'];
$handler->display->display_options['fields'][$base_fields['published']]['alter']['url_encode'] = 0;
$handler->display->display_options['fields'][$base_fields['published']]['required'] = 0;
$handler->display->display_options['fields'][$base_fields['published']]['exists'] = 0;
/* Field: Record Maintained By */
$handler->display->display_options['fields'][$base_fields['maintainers']]['id'] = $base_fields['maintainers'];
$handler->display->display_options['fields'][$base_fields['maintainers']]['table'] = $view->base_table;
$handler->display->display_options['fields'][$base_fields['maintainers']]['field'] = $base_fields['maintainers'];
$handler->display->display_options['fields'][$base_fields['maintainers']]['alter']['url_encode'] = 0;
$handler->display->display_options['fields'][$base_fields['maintainers']]['required'] = 0;
$handler->display->display_options['fields'][$base_fields['maintainers']]['exists'] = 0;
// Field: Record Owned By 
$handler->display->display_options['fields'][$base_fields['owner']]['id'] = $base_fields['owner'];
$handler->display->display_options['fields'][$base_fields['owner']]['table'] = $view->base_table;
$handler->display->display_options['fields'][$base_fields['owner']]['field'] = $base_fields['owner'];
$handler->display->display_options['fields'][$base_fields['owner']]['alter']['url_encode'] = 0;
$handler->display->display_options['fields'][$base_fields['owner']]['required'] = 0;
$handler->display->display_options['fields'][$base_fields['owner']]['exists'] = 0;

  $handler->display->display_options['fields']['subject_id_rewrite']['id'] = 'subject_id_rewrite';
  $handler->display->display_options['fields']['subject_id_rewrite']['table'] = 'views';
  $handler->display->display_options['fields']['subject_id_rewrite']['field'] = 'nothing';
  $handler->display->display_options['fields']['subject_id_rewrite']['label'] = 'Id';
  $handler->display->display_options['fields']['subject_id_rewrite']['alter']['text'] = '['.$subject_id_field.']';
  $handler->display->display_options['fields']['subject_id_rewrite']['exclude'] = TRUE;
  

/* Filter criterion: Published */
$handler->display->display_options['filters'][$base_fields['published']]['id'] = $base_fields['published'];
$handler->display->display_options['filters'][$base_fields['published']]['table'] = $view->base_table;
$handler->display->display_options['filters'][$base_fields['published']]['field'] = $base_fields['published'];
$handler->display->display_options['filters'][$base_fields['published']]['operator'] = '~=';
//$handler->display->display_options['filters'][$base_fields['published']]['value'] = 'pending';
$handler->display->display_options['filters'][$base_fields['published']]['exposed'] = TRUE;
$handler->display->display_options['filters'][$base_fields['published']]['expose']['operator_id'] = $resource_name.'_'.$base_fields['published'].'_op';
$handler->display->display_options['filters'][$base_fields['published']]['expose']['label'] = 'Published';
$handler->display->display_options['filters'][$base_fields['published']]['expose']['operator'] = $resource_name.'_'.$base_fields['published'].'_op';
$handler->display->display_options['filters'][$base_fields['published']]['expose']['identifier'] = $base_fields['published'];
$handler->display->display_options['filters'][$base_fields['published']]['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
);
$handler->display->display_options['filters'][$base_fields['published']]['is_grouped'] = TRUE;
$handler->display->display_options['filters'][$base_fields['published']]['group_info']['label'] = 'Published';
$handler->display->display_options['filters'][$base_fields['published']]['group_info']['identifier'] = $base_fields['published'];
$handler->display->display_options['filters'][$base_fields['published']]['group_info']['default_group'] = '1';
$handler->display->display_options['filters'][$base_fields['published']]['group_info']['group_items'] = array(
  1 => array(
    'title' => 'Pending',
    'operator' => '~=',
    'value' => 'pending',
  ),
  2 => array(
    'title' => 'Yes',
    'operator' => '~=',
    'value' => 'yes',
  ),
  3 => array(
    'title' => 'No',
    'operator' => '~=',
    'value' => 'no',
  ),
4 => array(
    'title' => 'Reviewed',
    'operator' => '~=',
    'value' => 'reviewed',
  ),
);
$handler->display->display_options['filters'][$base_fields['published']]['sparql_options'] = array(
  'value_type' => 'string',
  'language' => '0',
);

// Exposed filter: title.
  $handler->display->display_options['filters'][$base_fields['title']]['id'] = $base_fields['title'];
  $handler->display->display_options['filters'][$base_fields['title']]['table'] = $view->base_table;
  $handler->display->display_options['filters'][$base_fields['title']]['field'] = $base_fields['title'];
  $handler->display->display_options['filters'][$base_fields['title']]['operator'] = 'search';
  $handler->display->display_options['filters'][$base_fields['title']]['exposed'] = TRUE;
  $handler->display->display_options['filters'][$base_fields['title']]['expose']['operator_id'] = $base_fields['title'].'_op';
  $handler->display->display_options['filters'][$base_fields['title']]['expose']['label'] = 'Search '.$view_spec->getLabel();
  $handler->display->display_options['filters'][$base_fields['title']]['expose']['operator'] = $base_fields['title'].'_op';
  $handler->display->display_options['filters'][$base_fields['title']]['expose']['identifier'] = 'name';
  $handler->display->display_options['filters'][$base_fields['title']]['expose']['required'] = 0;
  $handler->display->display_options['filters'][$base_fields['title']]['expose']['multiple'] = FALSE;
  $handler->display->display_options['filters'][$base_fields['title']]['sparql_options'] = array(
    'value_type' => 'string',
    'language' => '0',
  );

/* Filter criterion: Record Maintained By */
$handler->display->display_options['filters'][$base_fields['maintainers']]['id'] = $base_fields['maintainers'];
$handler->display->display_options['filters'][$base_fields['maintainers']]['table'] = $view->base_table;
$handler->display->display_options['filters'][$base_fields['maintainers']]['field'] = $base_fields['maintainers'];
$handler->display->display_options['filters'][$base_fields['maintainers']]['operator'] = '~=';
$handler->display->display_options['filters'][$base_fields['maintainers']]['exposed'] = TRUE;
$handler->display->display_options['filters'][$base_fields['maintainers']]['expose']['operator_id'] = $resource_name.'_'.$base_fields['maintainers'].'_op';
$handler->display->display_options['filters'][$base_fields['maintainers']]['expose']['label'] = 'Record Maintained By';
$handler->display->display_options['filters'][$base_fields['maintainers']]['expose']['operator'] = $resource_name.'_'.$base_fields['maintainers'].'_op';
$handler->display->display_options['filters'][$base_fields['maintainers']]['expose']['identifier'] = $base_fields['maintainers'];
$handler->display->display_options['filters'][$base_fields['maintainers']]['sparql_options'] = array(
  'value_type' => 'string',
  'language' => '0',
);

/* Filter criterion: Record Owned By */
$handler->display->display_options['filters'][$base_fields['owner']]['id'] = $base_fields['owner'];
$handler->display->display_options['filters'][$base_fields['owner']]['table'] = $view->base_table;
$handler->display->display_options['filters'][$base_fields['owner']]['field'] = $base_fields['owner'];
$handler->display->display_options['filters'][$base_fields['owner']]['operator'] = '~=';
$handler->display->display_options['filters'][$base_fields['owner']]['exposed'] = TRUE;
$handler->display->display_options['filters'][$base_fields['owner']]['expose']['operator_id'] = $resource_name.'_'.$base_fields['owner'].'_op';
$handler->display->display_options['filters'][$base_fields['owner']]['expose']['label'] = 'Record Owned By';
$handler->display->display_options['filters'][$base_fields['owner']]['expose']['operator'] = $resource_name.'_'.$base_fields['owner'].'_op';
$handler->display->display_options['filters'][$base_fields['owner']]['expose']['identifier'] = $base_fields['owner'];
$handler->display->display_options['filters'][$base_fields['owner']]['sparql_options'] = array(
  'value_type' => 'string',
  'language' => '0',
);

  // Contextual filters.
  __curios_rdf_type_filter($handler, $view, $view_spec);

  return $handler;
}



/**
 * Filters a view by individual URI.
 */
function __curios_uri_filter(&$handler, $view, $view_spec) {
  $config = curios_configuration();
  $resource_name = $view_spec->getResource()->getMachineName();
  $handler->display->display_options['arguments'][$resource_name]['id'] = $resource_name;
  $handler->display->display_options['arguments'][$resource_name]['table'] = $view->base_table;
  $handler->display->display_options['arguments'][$resource_name]['field'] = $resource_name;
  $handler->display->display_options['arguments'][$resource_name]['default_action'] = 'not found';
  $handler->display->display_options['arguments'][$resource_name]['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments'][$resource_name]['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments'][$resource_name]['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments'][$resource_name]['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments'][$resource_name]['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments'][$resource_name]['sparql_options'] = array(
    'value_type' => 'uri',
    'language' => '0',
    'code' => 'return \'' . $config->getDefaultNamespace() . '\'.$this->argument;',
  );
}

/**
 * Creates a blank line in a field listing.
 */
function __curios_field_newline(&$handler) {
  static $c = 0;
  $field_name = 'newline_'.$c++;
  $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
  $handler->display->display_options['fields'][$field_name]['table'] = 'views';
  $handler->display->display_options['fields'][$field_name]['field'] = 'nothing';
  $handler->display->display_options['fields'][$field_name]['ui_name'] = 'New Line';
  $handler->display->display_options['fields'][$field_name]['label'] = '';
  $handler->display->display_options['fields'][$field_name]['alter']['text'] = '<br/>';
}
