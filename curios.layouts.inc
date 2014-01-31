<?php
/*
 * curios.layouts.inc
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
 * Implements hook_default_panels_layout.
 *
 * Defines the layout used on subject details pages.
 */
function curios_default_panels_layout() {
  $layouts = array();

$layout = new stdClass();
$layout->disabled = FALSE; /* Edit this to true to make a default layout disabled initially */
$layout->api_version = 1;
$layout->name = 'ldcms_details_page_layout';
$layout->admin_title = 'Subject Page Layout';
$layout->admin_description = '';
$layout->category = 'CURIOS';
$layout->plugin = 'flexible';
$layout->settings = array(
  'items' => array(
    'canvas' => array(
      'type' => 'row',
      'contains' => 'column',
      'children' => array(
        0 => 'main',
      ),
      'parent' => NULL,
    ),
    'main' => array(
      'type' => 'column',
      'width' => 100,
      'width_type' => '%',
      'children' => array(
        0 => 'main-row',
	1 => 'comment_region',
      ),
      'parent' => 'canvas',
    ),
    'comment_region' => array(
      'type' => 'region',
      'title' => 'Comments Region',
      'width' => 100,
      'width_type' => '%',
      'parent' => 'main',
      'class' => '',
    ),
    'main-row' => array(
      'type' => 'row',
      'contains' => 'column',
      'children' => array(
        0 => 2,
        1 => 3,
      ),
      'parent' => 'main',
      'class' => '',
    ),
    
    2 => array(
      'type' => 'column',
      'width' => '80',
      'width_type' => '%',
      'parent' => 'main-row',
      'children' => array(
        0 => 4,
        1 => 5,
        2 => 6,
        3 => 7,
      ),
      'class' => 'Col #1',
    ),
    3 => array(
      'type' => 'column',
      'width' => '20',
      'width_type' => '%',
      'parent' => 'main-row',
      'children' => array(
        0 => 8,
      ),
      'class' => 'Col #2',
    ),
    4 => array(
      'type' => 'row',
      'contains' => 'region',
      'children' => array(
        0 => 'admin_region',
      ),
      'parent' => '2',
      'class' => 'curios-admin-row',
    ),
    5 => array(
      'type' => 'row',
      'contains' => 'region',
      'children' => array(
        0 => 'summary_region',
      ),
      'parent' => '2',
      'class' => 'curios-summary-row',
    ),
    6 => array(
      'type' => 'row',
      'contains' => 'region',
      'children' => array(
        0 => 'properties_region',
      ),
      'parent' => '2',
      'class' => '',
    ),
    7 => array(
      'type' => 'row',
      'contains' => 'region',
      'children' => array(
        0 => 'image_gallery_region',
      ),
      'parent' => '2',
      'class' => '',
    ),
    8 => array(
      'type' => 'row',
      'contains' => 'region',
      'children' => array(
        0 => 'relationships_region',
      ),
      'parent' => '3',
      'class' => '',
    ),
    'admin_region' => array(
      'type' => 'region',
      'title' => 'Admin Region',
      'width' => 100,
      'width_type' => '%',
      'parent' => '4',
      'class' => 'curios-admin',
    ),
    'summary_region' => array(
      'type' => 'region',
      'title' => 'Summary Region',
      'width' => 100,
      'width_type' => '%',
      'parent' => '5',
      'class' => 'curios-summary',
    ),
    'properties_region' => array(
      'type' => 'region',
      'title' => 'Properties Region',
      'width' => 100,
      'width_type' => '%',
      'parent' => '6',
      'class' => 'curios-properties',
    ),
    'image_gallery_region' => array(
      'type' => 'region',
      'title' => 'Image Gallery Region',
      'width' => 100,
      'width_type' => '%',
      'parent' => '7',
      'class' => 'curios-image-gallery',
    ),
    'relationships_region' => array(
      'type' => 'region',
      'title' => 'Relationships Region',
      'width' => 100,
      'width_type' => '%',
      'parent' => '8',
      'class' => 'curios-relationships',
    ),
  ),
);

  $layouts['subject_page_layout'] = $layout;

  return $layouts;
}
