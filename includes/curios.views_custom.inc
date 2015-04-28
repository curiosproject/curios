<?php
/*
 * curios.views_custom.inc
 * 
 * Copyright (c) 2011-2015, Hai Nguyen  (hai.nguyen@abdn.ac.uk) Stuart Taylor (staylor@abdn.ac.uk),
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
 * Override listings view for hc_image_file.
 */
function __curios_generate_display_listing_hc_image_file(&$view, &$view_spec, $base_fields) {
  return __curios_remove_image_file_column($view, $view_spec, $base_fields);
}
function __curios_generate_display_listing_hc_sound_file(&$view, &$view_spec, $base_fields) {
  return __curios_remove_image_file_column($view, $view_spec, $base_fields);
}

/**
 * Override summary view for hc_image_file.
 */
function __curios_generate_display_summary_hc_image_file(&$view, &$view_spec, $base_fields) {
  return __curios_remove_search_link($view, $view_spec, $base_fields);
}
function __curios_generate_display_summary_hc_sound_file(&$view, &$view_spec, $base_fields) {
  return __curios_remove_search_link($view, $view_spec, $base_fields);;
}


/**
 * Override image gallery view for hc_image_file.
 */
function __curios_generate_display_images_hc_image_file(&$view, &$view_spec, $base_fields) {
  return FALSE;
}
function __curios_generate_display_images_hc_sound_file(&$view, &$view_spec, $base_fields) {
  return FALSE;
}

/**
 * Remove image file column from listing.
 */
function __curios_remove_image_file_column(&$view, &$view_spec, $base_fields) {
  $config = curios_configuration();
  $resource = $view_spec->getResource();
  $resource_name = $resource->getMachineName();
  $image_file = $resource_name.'_'.$config->getImageRelationshipFieldId();
  

  // Remove image file column.
  $handler = __curios_generate_display('listing', $view, $view_spec, $base_fields, TRUE);
  unset($handler->display->display_options['style_options']['columns'][$image_file]);
  unset($handler->display->display_options['style_options']['info'][$image_file]);
  unset($handler->display->display_options['fields'][$image_file]);

  return $handler;
}


/**
 * Remove searchlink.
 */
function __curios_remove_search_link(&$view, &$view_spec, $base_fields) {
  $handler = __curios_generate_display('summary', $view, $view_spec, $base_fields, TRUE);
  unset($handler->display->display_options['fields']['searchlink']);
  return $handler;
}

/**
 * Override properties view for hc_image_file.
 */
function __curios_generate_display_properties_hc_image_file(&$view, &$view_spec, $base_fields) {
  // FIXME there is a lot of duplicated code from __curios_generate_display_properties_default here.
  $config = curios_configuration();
  $resource = $view_spec->getResource();
  $resource_name = $resource->getMachineName();

  // Title/description fields.
  $title_field_name = $resource_name.'_'.$view_spec->getTitleFieldId();
  $description_field_name = $resource_name.'_'.$view_spec->getDescriptionFieldId();

  // DateRange.
  $date_range_resource = $config->getDateRangeResource();
  $date_range_from_id = $config->getDateRangeFromId();
  $date_range_to_id = $config->getDateRangeToId();

  /* Display: Properties */
  $handler = $view->new_display('block', 'Properties', 'properties');
  $handler->display->display_options['query']['type'] = 'views_query';

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

  // Pager options.
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

  // dc:title
  $handler->display->display_options['fields'][$base_fields['title']]['id'] = $base_fields['title'];
  $handler->display->display_options['fields'][$base_fields['title']]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$base_fields['title']]['field'] = $base_fields['title'];
  $handler->display->display_options['fields'][$base_fields['title']]['label'] = '';
  $handler->display->display_options['fields'][$base_fields['title']]['exclude'] = TRUE;
  $handler->display->display_options['fields'][$base_fields['title']]['required'] = 1;

  // hc:title
  $handler->display->display_options['fields'][$title_field_name]['id'] = $title_field_name;
  $handler->display->display_options['fields'][$title_field_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$title_field_name]['field'] = $title_field_name;
  $handler->display->display_options['fields'][$title_field_name]['label'] = '';
  $handler->display->display_options['fields'][$title_field_name]['exclude'] = TRUE;
  $handler->display->display_options['fields'][$title_field_name]['required'] = 1;

  // hc:description
  $handler->display->display_options['fields'][$description_field_name]['id'] = $description_field_name;
  $handler->display->display_options['fields'][$description_field_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$description_field_name]['field'] = $description_field_name;
  $handler->display->display_options['fields'][$description_field_name]['label'] = '';
  $handler->display->display_options['fields'][$description_field_name]['exclude'] = TRUE;
  $handler->display->display_options['fields'][$description_field_name]['required'] = 0;

    // Field: file.
  $field_name = $resource_name.'_'.$config->getURLFieldId();
  $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
  $handler->display->display_options['fields'][$field_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$field_name]['field'] = $field_name;
  $handler->display->display_options['fields'][$field_name]['label'] = '';
  $handler->display->display_options['fields'][$field_name]['exclude'] = TRUE;
  $handler->display->display_options['fields'][$field_name]['required'] = 1;

  $image_url_field = $config->getImageResourceId() .'_'.$config->getURLFieldId();
  $handler->display->display_options['fields']['curios_image_thumbnail_field']['id'] = 'curios_image_thumbnail_field';
  $handler->display->display_options['fields']['curios_image_thumbnail_field']['table'] = 'views';
  $handler->display->display_options['fields']['curios_image_thumbnail_field']['field'] = 'curios_image_thumbnail_field';
  $handler->display->display_options['fields']['curios_image_thumbnail_field']['label'] = '';
  $handler->display->display_options['fields']['curios_image_thumbnail_field']['alter']['text'] = "[$image_url_field]";
  $handler->display->display_options['fields']['curios_image_thumbnail_field']['alter']['make_link'] = FALSE;
  $handler->display->display_options['fields']['curios_image_thumbnail_field']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['curios_image_thumbnail_field']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['curios_image_thumbnail_field']['title_field'] = $base_fields['title'];
  $handler->display->display_options['fields']['curios_image_thumbnail_field']['disable_thumbnail'] = TRUE;

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
 * Generate properties display for sound files, override image files display.
 */
function __curios_generate_display_properties_hc_sound_file(&$view, &$view_spec, $base_fields) {
  $config = curios_configuration();
  $resource = $view_spec->getResource();
  $resource_name = $resource->getMachineName();

  $handler = __curios_generate_display_properties_hc_image_file($view, $view_spec, $base_fields);
  unset($handler->display->display_options['fields']['curios_image_thumbnail_field']);

  // Update and reposition URL field.
  $url_field_name = $resource_name.'_'.$config->getURLFieldId();
  $url_field = $handler->display->display_options['fields'][$url_field_name];
  unset($handler->display->display_options['fields'][$url_field_name]);

  $url_field['label'] = '';
  $url_field['exclude'] = FALSE;
  $url_field['alter']['alter_text'] = 1;
  $url_field['alter']['make_link'] = 1;
  $url_field['alter']['path'] = "[$url_field_name]";
  $url_field['alter']['text'] = 'Go to file';

  __curios_field_newline($handler);
  $handler->display->display_options['fields'][$url_field_name] = $url_field;


  $handler->display->display_options['fields']['curios_sound_handler_field']['id'] = 'curios_sound_handler_field';
  $handler->display->display_options['fields']['curios_sound_handler_field']['table'] = 'views';
  $handler->display->display_options['fields']['curios_sound_handler_field']['field'] = 'curios_sound_handler_field';
  $handler->display->display_options['fields']['curios_sound_handler_field']['label'] = '';
  $handler->display->display_options['fields']['curios_sound_handler_field']['alter']['text'] = "[$url_field_name]";
  $handler->display->display_options['fields']['curios_sound_handler_field']['alter']['make_link'] = FALSE;
  $handler->display->display_options['fields']['curios_sound_handler_field']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['curios_sound_handler_field']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['curios_sound_handler_field']['title_field'] = $base_fields['title'];


  return $handler;
}
