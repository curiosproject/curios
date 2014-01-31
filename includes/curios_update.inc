<?php
/*
 * curios_update.inc
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
 
require_once('curios_update_editor.inc');

/**
 * Page callback.
 *
 * Displays the main 'Manage Repository' page.
 */
function curios_manage_page() {
  $page = array();

  $base_path = base_path() . 'curios/manage';
  $content = <<<EOT
<p>From this page you can create, edit and delete records in the repository.</p>
<ul>
<li><a href="$base_path/create">Create a new record</a></li>
<li><a href="$base_path/edit">Edit or delete an existing record</a></li>
</ul>
<p>Choose an action from the menu to continue.</p>
<ul>
<li><a href="$base_path/tools">Repository administration tools</a></li>
</ul>
EOT;
  $page[] = array('#markup' => $content);

  return $page;
}

/**
 * Page callback.
 *
 * Displays the 'Admin Tools' page.
 */
function curios_admin_tools_page() {
  $page = array();
  $page[] = array('#markup' => '<p>This page contains a selection of admin tools for the Hebridean Connections repository.</p>');
  $page[] = curios_latest_records();

  return $page;
}

/**
 * Genearte HTML for latest records list.
 */
function curios_latest_records($n = 15) {
  $latest_records = _curios_latest_record_identifiers($n);

  $content = '';
  $content .= '<h2>Recently created records:</h2>';
  $content .= '<ul class="plain-list">';
  foreach ($latest_records as $id=>$title) {
    $content .= "<li><input type=\"text\" size=\"8\" value=\"$id\" readonly=\"readonly\" /> &nbsp; $title </li>";
  }
  $content .= '</ul>';

  return array('#markup' => $content);
}




/**
 * Ajax callback for latest records list from hook_menu,
 */
function curios_latest_records_ajax($page_callback_result) {
  print drupal_render($page_callback_result);
  drupal_page_footer();
}

/**
 * Loads a SPARQL Views resource type.
 */
function curios_resource_type_load($resource_name) {
  if (!empty($resource_name)) {
    $resource_type = sparql_views_resource_type_load($resource_name);
    
    if ($resource_type != NULL) {
      return $resource_type;
    } else {
      return FALSE;
    }
  }

  return $resource_name;
}

/**
 * Form callback.
 *
 * Lists the resources that can be created,
 */
function curios_manage_insert_form($form, &$form_state) {
  $form = array();

  $form['type'] = curios_resources_form_select();
  $form['submit'] = array('#type' => 'submit', '#value' => 'Next');
  
  return $form;
}

/**
 * Submit handler.
 *
 * Redirect the insert form to the appropriate insert form page.
 */
function curios_manage_insert_form_submit($form, &$form_state) {
  $type = $form_state['values']['type'];
  $path = "curios/manage/create/$type";

  $form_state['redirect'] = array($path, array(), 302);
}

/**
 * Form callback.
 *
 * Gets the browsing class and subject id of the reocrd to be updated.
 */
function curios_manage_update_form($form, &$form_state) {
  $form = array();

  $form['type'] = curios_resources_form_select();
  $form['subject_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject Id'),
    '#required' => TRUE,
    '#size' => '12',
  );
  $form['submit'] = array('#type' => 'submit', '#value' => 'Next');

  return $form;
}

/**
 * Submit handler.
 *
 * Redirects to the appropriate update page.
 */
function curios_manage_update_form_submit($form, &$form_state) {
  $type = $form_state['values']['type'];
  $id = $form_state['values']['subject_id'];
  $path = "curios/manage/edit/$type/$id";

  $form_state['redirect'] = array($path, array(), 302);
}

/**
 * Submit handler.
 *
 * Removes a record from the triple store.
 */
function curios_delete_form_submit($form, &$form_state) {
  // TODO add confirm form
  $subject_id = $form_state['values']['identifier'];
  $success = _curios_subject_delete($subject_id);

  if ($success) {
    drupal_set_message("The record has been deleted successfully  (ID: $subject_id).", 'status', FALSE);
    watchdog('curios_activity',t('Delete %recordID'),array('%recordID'=>$subject_id),WATCHDOG_INFO,$link = NULL);
    $form_state['redirect'] = array("curios/manage", array(), 302);
  } else {
    drupal_set_message("Failed to delete record.", 'error', FALSE);
  }
}

/**
 * Generates a form select element from the browsing classes in the configuration.
 */
function curios_resources_form_select() {
  $config = curios_configuration();
  $options = array();
  $resources = entity_load('sparql_views_resource_type');

  foreach ($resources as $entity) {
   
    if ($entity->name == $config->getDefaultResourceId() ||
        $config->getResource($entity->name) == NULL) {
      continue;
    }
    $options[$entity->name] = $entity->label;
  }

  return array(
    '#type' => 'select',
    '#empty_option' => '- Select record type -',
    '#required' => TRUE,
    '#options' => $options,
  );
}

/**
 * Page callback.
 *
 * Insert Record form page.
 */
function curios_insert_form_page($resource_type) {
  $page = array();
  $page[] = array('#markup' => "<p>Complete the form below to create a new record.</p>");
  $page[] = drupal_get_form('curios_insert_form', $resource_type);
  return $page;
}

/**
 * Page callback.
 *
 * Page to select to resource type to be created.
 */
function curios_insert_page() {
  $page = array();
  $page[] = array('#markup' => "<p>Select the record type below then click 'Next' to continue.</p>");
  $page[] = drupal_get_form('curios_manage_insert_form');

  return $page;
}

/**
 * Form callback.
 *
 * Insert record form. This form accepts title, description and literal fields.
 */
function curios_insert_form($form, $form_state, $resource_type) {
  $config = curios_configuration();
  $browsing_class = $config->getResource($resource_type->name);
  $view_spec_id = $config->getViewIdForResource($browsing_class->getId());
  $view_spec = $config->getViewSpec($view_spec_id);

  $entity_info = entity_get_info('sparql_views_resource');
  $rdf_mapping = $entity_info['bundles'][$resource_type->name]['rdf_mapping'];
  $field_instances = field_read_instances(array(
    'entity_type' => 'sparql_views_resource',
    'bundle' => $resource_type->name));

  $break = array('#markup' => '<br/>');

  $form = array();
  $form['status'] = array('#markup' => "<h3>Create new: <strong>".$resource_type->label."</strong></h3>");//<span style=\"font-size: 0.8em; text-style: italic;\">(".$resource_type->name.")</span>
  $form['resource'] = array('#type' => 'hidden', '#value' => $resource_type->name);

  // Get title and description fields from view spec.
  $title_field = $config->getField($view_spec->getTitleFieldId());
  $description_field = $config->getField($view_spec->getDescriptionFieldId());

  $form[$title_field->getId()] = array(
    '#type' => 'textfield',
    '#title' => t($title_field->getLabel()),
    '#required' => TRUE,
    '#size' => '80',
    '#field_suffix' => '<span class="rdf-predicate">('. $rdf_mapping[$title_field->getId()]['predicates'][0] .')</span>',
  );
  $form[$description_field->getId()] = array(
    '#type'=>'text_format',
    '#title' => t($description_field->getLabel()),
    '#required' => FALSE,
    '#cols' => '80',
    '#rows' => '4',
    '#format' => 'filtered_html',
    '#field_suffix' => '<span class="rdf-predicate">('. $rdf_mapping[$description_field->getId()]['predicates'][0] .')</span>',
  );
  $form[] = $break;

  //$form['submit'] = array('#type' => 'submit', '#value' => 'Create New Record');

  $form['submit_create'] = array(
    '#type' => 'submit',
    '#value' => t('Save & Create another'),
    '#submit' => array('curios_insert_form_submit_then_create'),
  );
  $form['submit_edit'] = array(
    '#type' => 'submit',
    '#value' => t('Save & Edit'),
    '#submit' => array('curios_insert_form_submit_then_edit'),
  );

  return $form;
}

function curios_insert_form_submit_then_create($form, &$form_state) {
  curios_insert_form_submit($form, $form_state, 'create');
}

function curios_insert_form_submit_then_edit($form, &$form_state) {
  curios_insert_form_submit($form, $form_state, 'edit');
}

/**
 * Submit handler.
 *
 * Processes the insert form and builds the set of triples to be inserted.
 */
function curios_insert_form_submit($form, &$form_state, $redirect = 'edit') {
  $config = curios_configuration();

  $resource_name = $form_state['values']['resource'];
  //$resource_type = sparql_views_resource_type_load($resource_name);
  $entity_info = entity_get_info('sparql_views_resource');
  $rdf_mapping = $entity_info['bundles'][$resource_name]['rdf_mapping'];
  $field_instances = field_read_instances(array(
    'entity_type' => 'sparql_views_resource',
    'bundle' => $resource_name,));

  $browsing_class = $config->getResource($resource_name);
  $view_spec_id = $config->getViewIdForResource($browsing_class->getId());
  $view_spec = $config->getViewSpec($view_spec_id);
  $title_field = $config->getField($view_spec->getTitleFieldId());
  $description_field = $config->getField($view_spec->getDescriptionFieldId());
 

  $rdf_type = $rdf_mapping['rdftype'][0];
  $triples_insert = array();
  $required_fields = array($title_field->getId(), $description_field->getId());

  // Add required fields.
  foreach ($required_fields as $field_name) {
    $form_value = $form_state['values'][$field_name];

    if (is_array($form_value)) { // if using a formatter
      $form_value = $form_state['values'][$field_name]['value'];
    }

    $triples_insert[] = '      ' . $rdf_mapping[$field_name]['predicates'][0]  ." \"". __curios_escape_sparql($form_value) ."\"^^xsd:string;";
  }

   // enforce post-conditions: owner_field and maintainer_field are set to user's society code. publishedfield set to pending.
  $owner_field = $config->getField($config->getOwnerFieldId());
  $maintainer_field = $config->getField($config->getMaintainerFieldId());
  $published_field = $config->getField($config->getPublishedFieldId());
  $group_code = curios_get_user_groupcode();
  //  if current user has a group code, set new record's owner and maintainer to user's groupcode
  if (isset($group_code))
  {	$group_code = __curios_escape_sparql($group_code);
	$triples_insert[] = '      ' . $rdf_mapping[$owner_field->getId()]['predicates'][0]  ." \"$group_code\"^^xsd:string;";
	$triples_insert[] = '      ' . $rdf_mapping[$maintainer_field->getId()]['predicates'][0]  ." \"$group_code\"^^xsd:string;";
  }
  else 
	$triples_insert[] = '      ' . $rdf_mapping[$owner_field->getId()]['predicates'][0]  ." \"any\"^^xsd:string;";

  $triples_insert[] = '      ' . $rdf_mapping[$published_field->getId()]['predicates'][0]  ." \"pending\"^^xsd:string;";


  $triples_insert = array_unique($triples_insert);
  $triples_insert = join("\n", $triples_insert);

  $success = _curios_subject_insert($rdf_type, $triples_insert);
  $subject_id = _curios_fetch_max_identifier();

  if ($success) {
    drupal_set_message("The new record has been created successfully (ID: $subject_id).", 'status', FALSE);
    watchdog('curios_activity',t('Create %recordID' ),array('%recordID'=>$subject_id),WATCHDOG_INFO,$link = NULL);
    switch ($redirect) {
      case 'create':
        $path = "curios/manage/create/$resource_name";
        break;
      case 'edit':
      default:
        $path = "curios/manage/edit/$resource_name/$subject_id";
    }

    $form_state['redirect'] = array($path, array(), 302);
  } else {
    drupal_set_message("Failed to create record.", 'error', FALSE);
  }
}

/* Helper functions to check for special fields defined in the configuration. */

function __is_relationship_field($field_instance) { return $field_instance['ldcms_type'] == 'relationship'; }

function __is_identifier_field($field_instance) {
  $config = curios_configuration();
  return $field_instance['field_name'] == $config->getIdentifierFieldId();
}

function __is_title_field($field_instance) {
  $config = curios_configuration();
  return ($field_instance['field_name'] == $config->getTitleFieldId() || 
    $field_instance['field_name'] == 'hc_english_name' || 
    $field_instance['field_name'] == 'hc_title'); // FIXME check $resource title field.
}

function __is_description_field($field_instance) {
  $config = curios_configuration();
  return ($field_instance['field_name'] == $config->getDescriptionFieldId() || $field_instance['field_name'] == 'hc_description');
}

function __is_published_field($field_instance) {
  $config = curios_configuration();
  return $field_instance['field_name'] == $config->getPublishedFieldId();
}

function __is_special_field($field_instance, $config) { 
  return $field_instance['field_name'] == $config->getImageRelationshipFieldId() || // FIXME Image relationship should be treated as normal relationships. 
         $field_instance['field_name'] == $config->getOwnerFieldId() ||
         $field_instance['field_name'] == $config->getMaintainerFieldId() ||
         $field_instance['field_name'] == $config->getPublishedFieldId()||
	 $field_instance['field_name'] == $config->getEditorNotesFieldId();
}


