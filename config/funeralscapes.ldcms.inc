<?php
/*
 * funeralscapes.ldcms.inc
 * 
 * Copyright (c) 2011-2014, Hai Nguyen (hai.nguyen@abdn.ac.uk) Stuart Taylor (staylor@abdn.ac.uk),
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

$options = array(
  // Default/fallback class - is a super class of all base classes.
  'default_class' => 'hc:Subject',

  // Local identifier property and default prefix for new instances.
  'identifier_property' => 'hc:subjectID',
  'default_prefix' => 'fs',

  // Title and description properties for summary views etc.
  'title_property' => 'hc:title',
  'description_property' => 'hc:description',
    
  // Record metadata properties.
  'owner_property' => 'hc:ownedBySociety',
  'maintainer_property' => 'hc:maintainedBySociety',
  'published_property' => 'hc:approvedForPub',
  'editor_notes_property' => 'hc:editorNotes',

  // Image details for gallery displays.
  'image_class' => 'hc:ImageFile',
  'image_relationship_property' => 'hc:hasImageFile',
  'url_property' => 'hc:URL',

  // DateRange definition.
  'date_range_class' => 'hc:DateRange',
  'date_range_from' => 'hc:dateFrom',
  'date_range_to' => 'hc:dateTo',
  // Settings for map
  'map_settings' => array (
   // should be updated according to the property name defined below for coordinates
   'map_x_prop' =>'hc:easting',
   'map_y_prop' =>'hc:northing',
   // the map will appear after this field (choose the value of either 'map_x_prop' and 'map_y_prop')
   'map_position'=> 'hc:easting',
  ),

  // settings for comments
  'default_disqus_code' => 'curiosdemo',
);


/* Dublin Core fields. */

$fields[] = array(
  'property' => 'dc:title',
  'label'    => 'Title',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'dc:description',
  'label'    => 'Description',
  'type'     => 'text',
);

/* Date Range fields. */
$fields[] = array(
  'property' => 'hc:dateFrom',
  'label'    => 'Date From',
  'type'     => 'datetime',
);
$fields[] = array(
  'property' => 'hc:dateTo',
  'label'    => 'Date To',
  'type'     => 'datetime',
);

/* FILE IS AUTO GENERATED FROM HERE ON */
$namespaces = array(
	'dc' => 'http://purl.org/dc/terms/',
	'fs' => 'http://www.funeralscapes.org/funeralscapes.owl#',
	'hc' => 'http://www.hebrideanconnections.com/hebridean.owl#',
	'owl' => 'http://www.w3.org/2002/07/owl#',
	'rdf' => 'http://www.w3.org/1999/02/22-rdf-syntax-ns#',
	'xml' => 'http://www.w3.org/XML/1998/namespace',
	'xsd' => 'http://www.w3.org/2001/XMLSchema#',
	'rdfs' => 'http://www.w3.org/2000/01/rdf-schema#',
);
$all_records = array(
	'hc:ImageFile',
	'fs:Performance',
	'hc:SoundFile',
	'fs:Places',
	'fs:AcademicSource',
	'fs:VideoFile',
	'fs:Music',
);
$fields[] = array(
	'property' => 'hc:editorNotes',
	'label'    => 'Editor Notes',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'hc:ownedBySociety',
	'label'    => 'Owned By Society',
	'type'     => 'autocomplete',
);
$fields[] = array(
	'property' => 'hc:subjectID',
	'label'    => 'Subject ID',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'hc:URL',
	'label'    => 'URL',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'fs:typeOfPlaces',
	'label'    => 'Type of places',
	'type'     => 'autocomplete',
);
$fields[] = array(
	'property' => 'fs:weather',
	'label'    => 'Weather',
	'type'     => 'autocomplete',
);
$fields[] = array(
	'property' => 'hc:description',
	'label'    => 'Description',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'hc:easting',
	'label'    => 'Easting',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'hc:northing',
	'label'    => 'Northing',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'fs:type',
	'label'    => 'Type',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'fs:typeOfPerformance',
	'label'    => 'Type of Performance',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'hc:approvedForPub',
	'label'    => 'Approved for Publication',
	'type'     => 'autocomplete',
);
$fields[] = array(
	'property' => 'fs:emotion',
	'label'    => 'emotion',
	'type'     => 'autocomplete',
);
$fields[] = array(
	'property' => 'fs:abstract',
	'label'    => 'abstract',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'fs:author',
	'label'    => 'author',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'hc:maintainedBySociety',
	'label'    => 'maintainedBySociety',
	'type'     => 'autocomplete',
);
$fields[] = array(
	'property' => 'hc:title',
	'label'    => 'Title',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'fs:typeOfReferences',
	'label'    => 'type of references',
	'type'     => 'autocomplete',
);

$fields[] = array(
	'property' => 'fs:musicalInstrumentation',
	'label'    => 'Musical Instrumentation',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'fs:historicalPeriod',
	'label'    => 'Historical period',
	'type'     => 'autocomplete',
);
$fields[] = array(
	'property' => 'fs:datePerformed',
	'label'    => 'Date performed',
	'type'     => 'daterange',
);
$fields[] = array(
	'property' => 'fs:datePublished',
	'label'    => 'datePublished',
	'type'     => 'daterange',
);
$fields[] = array(
	'property' => 'fs:date',
	'label'    => 'date',
	'type'     => 'daterange',
);
$fields[] = array(
	'property' => 'fs:associatedWith',
	'label'    => 'associatedWith',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'fs:locatedAt',
	'label'    => 'locatedAt',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'fs:isHeardHere',
	'label'    => 'isHeardHere',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'hc:hasImageFile',
	'label'    => 'hasImageFile',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'fs:hasVideoFile',
	'label'    => 'hasVideoFile',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'fs:informationSource',
	'label'    => 'Information source',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'hc:hasSoundFile',
	'label'    => 'has Sound File',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'fs:isShownHere',
	'label'    => 'isShownHere',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'fs:contains',
	'label'    => 'contains',
	'type'     => 'relationship',
);
$browsing_classes[] = array(
	'label'       => 'Image File',
	'name'        => 'imagefile',
	'class'       => 'hc:ImageFile',
	'title'       => 'hc:title',
	'description' => 'hc:description',
);
$browsing_classes[] = array(
	'label'       => 'Performance',
	'name'        => 'performance',
	'class'       => 'fs:Performance',
	'title'       => 'hc:title',
	'description' => 'hc:description',
);
$browsing_classes[] = array(
	'label'       => 'Sound File',
	'name'        => 'soundfile',
	'class'       => 'hc:SoundFile',
	'title'       => 'hc:title',
	'description' => 'hc:description',
);
$browsing_classes[] = array(
	'label'       => 'Places',
	'name'        => 'places',
	'class'       => 'fs:Places',
	'title'       => 'hc:title',
	'description' => 'hc:description',
);
$browsing_classes[] = array(
	'label'       => 'Academic Source',
	'name'        => 'academicsource',
	'class'       => 'fs:AcademicSource',
	'title'       => 'hc:title',
	'description' => 'hc:description',
);
$browsing_classes[] = array(
	'label'       => 'Subject',
	'name'        => 'subject',
	'class'       => 'hc:Subject',
	'title'       => 'hc:title',
	'description' => 'hc:description',
);
$browsing_classes[] = array(
	'label'       => 'Video File',
	'name'        => 'videofile',
	'class'       => 'fs:VideoFile',
	'title'       => 'hc:title',
	'description' => 'hc:description',
);
$browsing_classes[] = array(
	'label'       => 'Music',
	'name'        => 'music',
	'class'       => 'fs:Music',
	'title'       => 'hc:title',
	'description' => 'hc:description',
);
$field_assignments['imagefile'] = array(
	'hc:editorNotes',
	'hc:ownedBySociety',
	'hc:subjectID',
	'hc:URL',
	'hc:description',
	//'fs:type',
	//'fs:typeOfPerformance',
	'hc:approvedForPub',
	//'fs:emotion',
	//'fs:abstract',
	//'fs:author',
	'hc:maintainedBySociety',
	'hc:title',
	//'fs:typeOfReferences',
	//'fs:musicalInstrumentation',
	'fs:historicalPeriod',
);
$field_assignments['performance'] = array(
	'hc:editorNotes',
	'hc:ownedBySociety',
	'hc:subjectID',
	'fs:weather',
	'hc:description',
	'fs:typeOfPerformance',
	'hc:approvedForPub',
	'fs:emotion',
	'hc:maintainedBySociety',
	'hc:title',
	'fs:typeOfReferences',
	'fs:musicalInstrumentation',
	'fs:historicalPeriod',
	'fs:datePerformed',
);
$field_assignments['soundfile'] = array(
	'hc:editorNotes',
	'hc:ownedBySociety',
	'hc:subjectID',
	'hc:URL',
	'fs:typeOfPlaces',
	'fs:weather',
	'hc:description',
	'hc:approvedForPub',
	'fs:emotion',
	'hc:maintainedBySociety',
	'hc:title',
	'fs:typeOfReferences',
	'fs:musicalInstrumentation',
	'fs:historicalPeriod',
);
$field_assignments['places'] = array(
	'hc:editorNotes',
	'hc:ownedBySociety',
	'hc:subjectID',
	'fs:typeOfPlaces',
	'fs:weather',
	'hc:description',
	'hc:easting',
	'hc:northing',
	'hc:approvedForPub',
	'hc:maintainedBySociety',
	'hc:title',
	'fs:historicalPeriod',
);
$field_assignments['academicsource'] = array(
	'hc:editorNotes',
	'hc:ownedBySociety',
	'hc:subjectID',
	'hc:URL',
	'hc:description',
	'fs:type',
	'hc:approvedForPub',
	'fs:abstract',
	'fs:author',
	'hc:maintainedBySociety',
	'hc:title',
	'fs:typeOfReferences',
	'fs:historicalPeriod',
	'fs:datePublished',
);
$field_assignments['subject'] = array(
	'hc:editorNotes',
	'hc:ownedBySociety',
	'hc:subjectID',
	'hc:URL',
	'fs:typeOfPlaces',
	'fs:weather',
	'hc:description',
	'hc:easting',
	'hc:northing',
	'fs:type',
	'fs:typeOfPerformance',
	'hc:approvedForPub',
	'fs:emotion',
	'fs:abstract',
	'fs:author',
	'hc:maintainedBySociety',
	'hc:title',
	'fs:typeOfReferences',
	'fs:musicalInstrumentation',
	'fs:historicalPeriod',
);
$field_assignments['videofile'] = array(
	'hc:editorNotes',
	'hc:ownedBySociety',
	'hc:subjectID',
	'hc:URL',
	'fs:weather',
	'hc:description',
	'fs:type',
	'fs:typeOfPerformance',
	'hc:approvedForPub',
	'fs:emotion',
	'hc:maintainedBySociety',
	'hc:title',
	'fs:typeOfReferences',
	'fs:musicalInstrumentation',
	'fs:historicalPeriod',
);
$field_assignments['music'] = array(
	'hc:editorNotes',
	'hc:ownedBySociety',
	'hc:subjectID',
	'fs:weather',
	'hc:description',
	'fs:type',
	'fs:typeOfPerformance',
	'hc:approvedForPub',
	'fs:emotion',
	'hc:maintainedBySociety',
	'hc:title',
	'fs:typeOfReferences',
	'fs:musicalInstrumentation',
	'fs:historicalPeriod',
);
$relationship_assignments['imagefile'][] = array(
	'property' => 'fs:associatedWith',
	'target'   => $all_records,
);
$relationship_assignments['imagefile'][] = array(
	'property' => 'fs:locatedAt',
	'target'   => 'fs:Places',
);

$relationship_assignments['imagefile'][] = array(
	'property' => 'fs:informationSource',
	'target'   => $all_records,
);

$relationship_assignments['imagefile'][] = array(
	'property' => 'fs:isShownHere',
	'target'   => $all_records,
);

$relationship_assignments['performance'][] = array(
	'property' => 'fs:associatedWith',
	'target'   => $all_records,
);
$relationship_assignments['performance'][] = array(
	'property' => 'fs:locatedAt',
	'target'   => 'fs:Places',
);
$relationship_assignments['performance'][] = array(
	'property' => 'fs:isHeardHere',
	'target'   => $all_records,
);
$relationship_assignments['performance'][] = array(
	'property' => 'hc:hasImageFile',
	'target'   => 'hc:ImageFile',
);
$relationship_assignments['performance'][] = array(
	'property' => 'fs:hasVideoFile',
	'target'   => 'fs:VideoFile',
);
$relationship_assignments['performance'][] = array(
	'property' => 'fs:informationSource',
	'target'   => $all_records,
);
$relationship_assignments['performance'][] = array(
	'property' => 'hc:hasSoundFile',
	'target'   => 'hc:SoundFile',
);
$relationship_assignments['performance'][] = array(
	'property' => 'fs:isShownHere',
	'target'   => $all_records,
);
$relationship_assignments['performance'][] = array(
	'property' => 'fs:contains',
	'target'   => $all_records,
);
$relationship_assignments['soundfile'][] = array(
	'property' => 'fs:associatedWith',
	'target'   => $all_records,
);
$relationship_assignments['soundfile'][] = array(
	'property' => 'fs:locatedAt',
	'target'   => 'fs:Places',
);
$relationship_assignments['soundfile'][] = array(
	'property' => 'fs:isHeardHere',
	'target'   => $all_records,
);

$relationship_assignments['soundfile'][] = array(
	'property' => 'fs:informationSource',
	'target'   => $all_records,
);

$relationship_assignments['soundfile'][] = array(
	'property' => 'fs:isShownHere',
	'target'   => $all_records,
);
$relationship_assignments['soundfile'][] = array(
	'property' => 'fs:contains',
	'target'   => $all_records,
);
$relationship_assignments['places'][] = array(
	'property' => 'fs:associatedWith',
	'target'   => $all_records,
);
$relationship_assignments['places'][] = array(
	'property' => 'fs:locatedAt',
	'target'   => 'fs:Places',
);
$relationship_assignments['places'][] = array(
	'property' => 'fs:isHeardHere',
	'target'   => $all_records,
);
$relationship_assignments['places'][] = array(
	'property' => 'hc:hasImageFile',
	'target'   => 'hc:ImageFile',
);
$relationship_assignments['places'][] = array(
	'property' => 'fs:hasVideoFile',
	'target'   => 'fs:VideoFile',
);
$relationship_assignments['places'][] = array(
	'property' => 'fs:informationSource',
	'target'   => $all_records,
);
$relationship_assignments['places'][] = array(
	'property' => 'hc:hasSoundFile',
	'target'   => 'hc:SoundFile',
);
$relationship_assignments['places'][] = array(
	'property' => 'fs:isShownHere',
	'target'   => $all_records,
);
$relationship_assignments['places'][] = array(
	'property' => 'fs:contains',
	'target'   => $all_records,
);
$relationship_assignments['academicsource'][] = array(
	'property' => 'fs:associatedWith',
	'target'   => $all_records,
);
$relationship_assignments['academicsource'][] = array(
	'property' => 'fs:locatedAt',
	'target'   => 'fs:Places',
);
$relationship_assignments['academicsource'][] = array(
	'property' => 'fs:isHeardHere',
	'target'   => $all_records,
);
$relationship_assignments['academicsource'][] = array(
	'property' => 'hc:hasImageFile',
	'target'   => 'hc:ImageFile',
);
$relationship_assignments['academicsource'][] = array(
	'property' => 'fs:hasVideoFile',
	'target'   => 'fs:VideoFile',
);
$relationship_assignments['academicsource'][] = array(
	'property' => 'fs:informationSource',
	'target'   => $all_records,
);
$relationship_assignments['academicsource'][] = array(
	'property' => 'hc:hasSoundFile',
	'target'   => 'hc:SoundFile',
);
$relationship_assignments['academicsource'][] = array(
	'property' => 'fs:isShownHere',
	'target'   => $all_records,
);
$relationship_assignments['academicsource'][] = array(
	'property' => 'fs:contains',
	'target'   => $all_records,
);
$relationship_assignments['subject'][] = array(
	'property' => 'fs:associatedWith',
	'target'   => $all_records,
);
$relationship_assignments['subject'][] = array(
	'property' => 'fs:locatedAt',
	'target'   => 'fs:Places',
);
$relationship_assignments['subject'][] = array(
	'property' => 'fs:isHeardHere',
	'target'   => $all_records,
);
$relationship_assignments['subject'][] = array(
	'property' => 'hc:hasImageFile',
	'target'   => 'hc:ImageFile',
);
$relationship_assignments['subject'][] = array(
	'property' => 'fs:hasVideoFile',
	'target'   => 'fs:VideoFile',
);
$relationship_assignments['subject'][] = array(
	'property' => 'fs:informationSource',
	'target'   => $all_records,
);
$relationship_assignments['subject'][] = array(
	'property' => 'hc:hasSoundFile',
	'target'   => 'hc:SoundFile',
);
$relationship_assignments['subject'][] = array(
	'property' => 'fs:isShownHere',
	'target'   => $all_records,
);
$relationship_assignments['subject'][] = array(
	'property' => 'fs:contains',
	'target'   => $all_records,
);
$relationship_assignments['videofile'][] = array(
	'property' => 'fs:associatedWith',
	'target'   => $all_records,
);
$relationship_assignments['videofile'][] = array(
	'property' => 'fs:locatedAt',
	'target'   => 'fs:Places',
);
$relationship_assignments['videofile'][] = array(
	'property' => 'fs:isHeardHere',
	'target'   => $all_records,
);

$relationship_assignments['videofile'][] = array(
	'property' => 'fs:informationSource',
	'target'   => $all_records,
);

$relationship_assignments['videofile'][] = array(
	'property' => 'fs:isShownHere',
	'target'   => $all_records,
);

$relationship_assignments['music'][] = array(
	'property' => 'fs:associatedWith',
	'target'   => $all_records,
);
$relationship_assignments['music'][] = array(
	'property' => 'fs:locatedAt',
	'target'   => 'fs:Places',
);
$relationship_assignments['music'][] = array(
	'property' => 'fs:isHeardHere',
	'target'   => $all_records,
);
$relationship_assignments['music'][] = array(
	'property' => 'hc:hasImageFile',
	'target'   => 'hc:ImageFile',
);
$relationship_assignments['music'][] = array(
	'property' => 'fs:hasVideoFile',
	'target'   => 'fs:VideoFile',
);
$relationship_assignments['music'][] = array(
	'property' => 'fs:informationSource',
	'target'   => $all_records,
);
$relationship_assignments['music'][] = array(
	'property' => 'hc:hasSoundFile',
	'target'   => 'hc:SoundFile',
);
$relationship_assignments['music'][] = array(
	'property' => 'fs:isShownHere',
	'target'   => $all_records,
);
$relationship_assignments['music'][] = array(
	'property' => 'fs:contains',
	'target'   => $all_records,
);
