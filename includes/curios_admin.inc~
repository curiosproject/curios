<?php
/*
 * curios_admin.inc
 *
 * Copyright (c) 2011-2013, Stuart Taylor (staylor@abdn.ac.uk), Hai Nguyen (hai.nguyen@abdn.ac.uk)
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

require('curios_field_install.inc');
require_once('curios_ldcms.inc');

/**
 * Implements hook_admin.
 *
 * Admin settings form found at admin/structure/ldcms.
 */
function curios_admin() {
  $form = array();

  $config_files = _curios_config_file_list();
  
  $form['config_files'] = array(
    '#type' => 'select',
    '#title' => t('LDCMS configuration file'),
    '#empty_option' => '- Select File -',
    '#default_value' => variable_get('ldcms_config'),
    '#required' => TRUE,
    '#options' => $config_files,
  );


  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced Options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

//  $form['fieldset']'quick'] = array(
//    '#type' => 'checkbox',
//    '#title' => t('Quick mode (perform a shallow diff on field and relationship assignments).'),
//  );

  $form['fieldset']['config-reload'] = array(
    '#type' => 'checkbox',
    '#title' => t('Reload configuration file only (does not add/remove Drupal fields).'),
  );

  $form['fieldset']['ldcms-disable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable LDCMS (use this before making changes to the configuration).'),
  );
  
  $form['fieldset']['remove-only'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove fields only (uninstall mode, does not create new entities).'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Load Configuration',
  );


 $form['map_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Ordnance Survey Map Settings for LDCMS'),
    '#weight' => 2,
    '#collapsible' => TRUE,
  );

 // default value is for curios.abdn.ac.uk
	 $form['map_settings']['osmap_api_key'] = array(
	  '#type' => 'textfield', 
	  '#title' => t('Ordnance Survey Map API key'), 
	  '#size' => 60, 
	  '#default_value' => variable_get('curios_osmap_api_key','BA08531D8339984EE0405F0AC86026A9'),
	  '#maxlength' => 128, 
	  '#required' => FALSE,
	  '#description' => t('(Optional) Ordnance Survey OpenSpace API key for mapping service. <i>Go to Ordnance Survey website to register your domain (eg, example.com) and get the key</i>. <b>If you don\'t need mapping services, leave this field blank.</b>'),
	 );

	$form['map_settings']['default_northing'] = array(
	  '#type' => 'textfield', 
	  '#title' => t('Default Northing for Ordnance Survey Map'), 
	  '#size' => 60, 
	  '#default_value' => variable_get('curios_default_northing','808250'),
	  '#maxlength' => 128, 
	  '#required' => FALSE,
	  '#description' => t('(Optional) Current default northing is for Old Aberdeen (808250).'),
	 );
	$form['map_settings']['default_easting'] = array(
	  '#type' => 'textfield', 
	  '#title' => t('Default Easting for Ordnance Survey Map'), 
	  '#size' => 60, 
	  '#default_value' => variable_get('curios_default_easting','393950'),
	  '#maxlength' => 128, 
	  '#required' => FALSE,
	  '#description' => t('(Optional) Current default easting is for Old Aberdeen (393950).'),
	 );
	$form['map_settings']['default_zoom_level'] = array(
	  '#type' => 'textfield', 
	  '#title' => t('Default Zoom Level for Map'), 
	  '#size' => 60, 
	  '#default_value' => variable_get('curios_default_zoom_level','3'),
	  '#maxlength' => 128, 
	  '#required' => FALSE,
	  '#description' => t('(Optional) Current default zoom level is 3. Increase to zoom in and decrease to zoom out.'),
	 );

	  $form['map_settings']['save_setings'] = array(
    	    '#type' => 'submit',
	    '#value' => 'Save Settings',
	    '#submit' => array('curios_admin_map_settings_submit'),
	  );


 $form['ldcms_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('General Settings for LDCMS'),
    '#weight' => 3,
    '#collapsible' => TRUE,
  );
 
     $form['ldcms_settings']['compute-inference'] = array(
    '#value' => 'Re-compute inferences',
    '#type' => 'submit', 
    '#submit' => array('curios_admin_compute_inference_submit'),
    '#prefix' => '<div style="color:'.((variable_get('curios_inference_updated')?'green':'red')).';">'.((variable_get('curios_inference_updated')?'The inference graph is up-to-dated':'There has been recent updates')).'.</div>',
    '#suffix' => '<div class="description">'.t('Recompute the inference graph. This is automatically run after an interval as a cron-job, or you can mannually run it by clicking the button.').'</div>',
  );
  return $form;
}

function curios_admin_compute_inference_submit($form, &$form_state) {
  if (_curios_trigger_inference())
	  drupal_set_message(t('The inference graph has been recomputed!'));
  else
	  drupal_set_message(t('The inference graph is up-to-dated. No recomputation required.'));
}


/**
 * Implements map settings_submit callback
 * 
 */
function curios_admin_map_settings_submit($form, &$form_state) {
  // set new key for the map
  if ($form_state['values']['osmap_api_key']!=variable_get('curios_osmap_api_key'))
	  variable_set('curios_osmap_api_key',$form_state['values']['osmap_api_key']);
  if ($form_state['values']['default_northing']!=variable_get('curios_default_northing')) 
	  variable_set('curios_default_northing',$form_state['values']['default_northing']);
  if ($form_state['values']['default_easting']!=variable_get('curios_default_easting')) 
	  variable_set('curios_default_easting',$form_state['values']['default_easting']);
  if ($form_state['values']['default_zoom_level']!=variable_get('curios_default_zoom_level')) 
	  variable_set('curios_default_zoom_level',$form_state['values']['default_zoom_level']);

  drupal_set_message(t('LDCMS Map settings have been saved.'));
}


/**
 * Implements hook_admin_submit.
 *
 * Submit handler, triggers (re)loading of the configuration, creation of fields, resources etc.
 */
function curios_admin_submit($form, &$form_state) {

  if ($form_state['values']['ldcms-disable']) { // Disable LDCMS only.
    drupal_set_message('LDCMS disabled.');
    variable_del('ldcms_installed');
    return;
  }

  $config_file_previous = variable_get('ldcms_config');
  $config_file_new = $form_state['values']['config_files'];
  variable_set('ldcms_config', $config_file_new);

  // Load old configuration.
  $config_previous = NULL;
  if ($config_file_previous != NULL) {
    $config_data_previous = curios_load_configuration_spec_from_database($config_file_previous);
    
    if ($config_data_previous != NULL) {
      $config_previous = curios_create_configuration($config_data_previous);
    }
  }

  // Load new configuration.
  $config_data_new = curios_load_configuration_spec($config_file_new);
  $config_new = curios_create_configuration($config_data_new);

  if ($form_state['values']['config-reload']) { // Config reload only.
    drupal_set_message('Configuration values reloaded.');
    variable_set('ldcms_installed', TRUE);
  } else { // Start field install batch.
    _curios_update_entity_batch_start($config_previous, $config_new, $form_state['values']['remove-only']);
  }
}

/**
 * List configuration files.
 *
 * Returns file names matching: config/CONFIG-NAME.ldcms.inc
 */
function _curios_config_file_list() {
  $config_path = drupal_get_path('module', 'curios') . '/config';

  $valid_files = function($f) {
    return preg_match('/^[a-z0-9].*.ldcms.inc$/i', $f);
  };

  $config_files = array_filter(scandir($config_path), $valid_files);
  $config_files = array_combine($config_files, $config_files);

  return $config_files;
}
