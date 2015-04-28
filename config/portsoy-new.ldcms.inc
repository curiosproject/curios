<?php
/*
 * portsoy.ldcms.inc
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
  'default_prefix' => 'po',

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
   'map_position'=> 'hc:northing',
  ),

  // settings for comments
  'default_disqus_code' => 'curiosdemo',
);


/* Dublin Core fields. */

$fields[] = array(
  'property' => 'hc:title',
  'label'    => 'Title',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:description',
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
   'rdf' => 'http://www.w3.org/1999/02/22-rdf-syntax-ns#',
   'rdfs' => 'http://www.w3.org/2000/01/rdf-schema#',
   'dc' => 'http://purl.org/dc/terms/',
   'owl' => 'http://www.w3.org/2002/07/owl#',
   'xsd' => 'http://www.w3.org/2001/XMLSchema#',
   'hc' => 'http://www.hebrideanconnections.com/hebridean.owl#',
   'po' => 'http://www.portsoy.com/portsoy.owl#',
);

$all_records = array(
   'po:Person',
   'hc:ImageFile',
   'po:InformationSource',
   'po:Location',
   'po:Residence',
   'po:SoundFile'
);

/* Literal Value Fields */

$fields[] = array(
   'property' => 'po:alternativeSurnames',
   'label'    => 'Alternative Surnames',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'hc:approvedForPub',
   'label'    => 'Approved for Publication?',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:easting',
   'label'    => 'Easting',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'hc:editorNotes',
   'label'    => 'Editor Notes',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'po:locationCode',
   'label'    => 'Location Code',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'po:locationType',
   'label'    => 'Location Type',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:maintainedBySociety',
   'label'    => 'Maintained by Society',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:northing',
   'label'    => 'Northing',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'po:occupation',
   'label'    => 'Occupation',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'po:otherNames',
   'label'    => 'Other Names',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'hc:ownedBySociety',
   'label'    => 'Owned by Society',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'po:sex',
   'label'    => 'Sex',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:subjectID',
   'label'    => 'Subject ID',
   'type'     => 'integer',
);
$fields[] = array(
   'property' => 'po:surname',
   'label'    => 'Surname',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'po:teeName',
   'label'    => 'TeeName',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'hc:URL',
   'label'    => 'URL',
   'type'     => 'text',
);
// added on 20/4/15

$fields[] = array(
   'property' => 'po:christianName',
   'label'    => 'Christian Name',
   'type'     => 'text',
);

$fields[] = array(
   'property' => 'po:serviceNo',
   'label'    => 'Service No',
   'type'     => 'text',
);

$fields[] = array(
   'property' => 'po:regiment',
   'label'    => 'Regiment',
   'type'     => 'text',
);

$fields[] = array(
   'property' => 'po:regiment',
   'label'    => 'Regiment',
   'type'     => 'text',
);

$fields[] = array(
   'property' => 'po:militaryRank',
   'label'    => 'Military Rank',
   'type'     => 'autocomplete',
);

$fields[] = array(
   'property' => 'hc:hasSoundFile',
   'label'    => 'Has Sound File',
   'type'     => 'relationship',
);

//end added 20/4/2015
$fields[] = array(
   'property' => 'po:dateOfBaptism',
   'label'    => 'Date of Baptism',
   'type'     => 'daterange',
);
$fields[] = array(
   'property' => 'po:dateOfBirth',
   'label'    => 'Date of Birth',
   'type'     => 'daterange',
);
$fields[] = array(
   'property' => 'po:dateOfDeath',
   'label'    => 'Date of Death',
   'type'     => 'daterange',
);
$fields[] = array(
   'property' => 'po:dateTaken',
   'label'    => 'Date Taken',
   'type'     => 'daterange',
);
$fields[] = array(
   'property' => 'po:dateOfMarriage',
   'label'    => 'Date of Marriage',
   'type'     => 'daterange',
);


/* Relationship Fields */

$fields[] = array(
   'property' => 'po:bornIn',
   'label'    => 'Born in',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'po:childOf',
   'label'    => 'Child of',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'po:parentOf',
   'label'    => 'Parent of',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:hasImageFile',
   'label'    => 'Has Image',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'po:informationSource',
   'label'    => 'Information Obtained from',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:isShownHere',
   'label'    => 'Shown Here',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'po:livedIn',
   'label'    => 'Lived in',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'po:livedInBy',
   'label'    => 'Lived in by',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'po:locatedIn',
   'label'    => 'Location in',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'po:marriedTo',
   'label'    => 'Married to',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'po:sameAs',
   'label'    => 'The Same as',
   'type'     => 'relationship',
);

/* Browsing Class Definitions */

$browsing_classes[] = array(
   'name'  => 'subjects',
   'label' => 'All Records',
   'class' => 'hc:Subject',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'images',
   'label' => 'Image Details',
   'class' => 'hc:ImageFile',
   'title' => 'hc:title',
   'description' => 'hc:description',
);

$browsing_classes[] = array(
   'name'  => 'sounds',
   'label' => 'Media Items',
   'class' => 'hc:SoundFile',
   'title' => 'hc:title',
   'description' => 'hc:description',
);

$browsing_classes[] = array(
   'name'  => 'infoSources',
   'label' => 'Information Sources',
   'class' => 'po:InformationSource',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'locations',
   'label' => 'Locations',
   'class' => 'po:Location',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'people',
   'label' => 'People',
   'class' => 'po:Person',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'residences',
   'label' => 'Residences',
   'class' => 'po:Residence',
   'title' => 'hc:title',
   'description' => 'hc:description',
);

/* Field Assignments */

$field_assignments['subjects'] = array(
   'hc:description',
   'hc:title',
   'hc:URL',
   'hc:approvedForPub',
   'hc:easting',
   'hc:editorNotes',
   'hc:maintainedBySociety',
   'hc:northing',
   'hc:ownedBySociety',
   'hc:subjectID',
   'po:alternativeSurnames',
   'po:dateOfBaptism',
   'po:dateOfBirth',
   'po:dateOfDeath',
   'po:dateOfMarriage',
   'po:dateTaken',
   'po:locationCode',
   'po:locationType',
   'po:occupation',
   'po:otherNames',
   'po:sex',
   'po:surname',
   'po:teeName',

);
$field_assignments['images'] = array(
   'hc:approvedForPub',
   'hc:maintainedBySociety',
   'hc:ownedBySociety',
   'hc:title',
   'hc:description',
   'hc:subjectID',
   'hc:editorNotes',
   'hc:URL',
   'po:dateTaken',
);

$field_assignments['sounds'] = array(
   'hc:approvedForPub',
   'hc:maintainedBySociety',
   'hc:ownedBySociety',
   'hc:title',
   'hc:description',
   'hc:subjectID',
   'hc:editorNotes',
   'hc:URL',
   'po:dateTaken',
);

$field_assignments['infoSources'] = array(
   'hc:approvedForPub',
   'hc:maintainedBySociety',
   'hc:ownedBySociety',
   'hc:title',
   'hc:description',
   'hc:subjectID',
   'hc:editorNotes',
);
$field_assignments['locations'] = array(
   'hc:approvedForPub',
   'hc:maintainedBySociety',
   'hc:ownedBySociety',
   'hc:title',
   'hc:description',
   'hc:subjectID',
   'hc:editorNotes',
   'po:locationType',
   'po:locationCode',
);
$field_assignments['people'] = array(
   'hc:approvedForPub',
   'hc:maintainedBySociety',
   'hc:ownedBySociety',
   'hc:title',
   'hc:description',
   'hc:subjectID',
   'hc:editorNotes',
   'po:alternativeSurnames',
   'po:occupation',
   'po:sex',
   'po:surname',
   'po:teeName',
   'po:otherNames',
   'po:dateOfBaptism',
   'po:dateOfBirth',
   'po:dateOfDeath',
   'po:dateOfMarriage',
   'po:militaryRank',
   'po:christianName',
   'po:serviceNo',
   'po:regiment',
);
$field_assignments['residences'] = array(
   'hc:approvedForPub',
   'hc:maintainedBySociety',
   'hc:ownedBySociety',
   'hc:title',
   'hc:description',
   'hc:subjectID',
   'hc:editorNotes',
   'hc:easting',
   'hc:northing',
);

/* Relationship Assignments */

/* Subjects */

$relationship_assignments['subjects'][] = array(
   'property' => 'po:bornIn',
   'target' => 'po:Location',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'po:childOf',
   'target' => 'po:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'po:informationSource',
   'target' => 'po:InformationSource',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'po:livedIn',
   'target' => array(
      'po:Location',
      'po:Residence',
   ),
);
$relationship_assignments['subjects'][] = array(
   'property' => 'po:livedInBy',
   'target' => 'po:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'po:locatedIn',
   'target' => 'po:Location',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'po:marriedTo',
   'target' => 'po:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'po:parentOf',
   'target' => 'po:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'po:sameAs',
   'target' => array(
      'po:Location',
      'po:Person',
      'po:Residence',
   ),
);
/* Image Details */
$relationship_assignments['images'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);

/* Information Sources */
$relationship_assignments['infoSources'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['infoSources'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
/* Locations */
$relationship_assignments['locations'][] = array(
   'property' => 'po:livedInBy',
   'target' => 'po:Person',
);
$relationship_assignments['locations'][] = array(
   'property' => 'po:locatedIn',
   'target' => 'po:Location',
);
$relationship_assignments['locations'][] = array(
   'property' => 'po:sameAs',
   'target' => 'po:Location',
);
$relationship_assignments['locations'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['locations'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
/* People */
$relationship_assignments['people'][] = array(
   'property' => 'po:bornIn',
   'target' => 'po:Location',
);
$relationship_assignments['people'][] = array(
   'property' => 'po:childOf',
   'target' => 'po:Person',
);
$relationship_assignments['people'][] = array(
   'property' => 'po:informationSource',
   'target' => 'po:InformationSource',
);
$relationship_assignments['people'][] = array(
   'property' => 'po:livedIn',
   'target' => array(
      'po:Residence',
      'po:Location',
   ),
);
$relationship_assignments['people'][] = array(
   'property' => 'po:marriedTo',
   'target' => 'po:Person',
);
$relationship_assignments['people'][] = array(
   'property' => 'po:parentOf',
   'target' => 'po:Person',
);
$relationship_assignments['people'][] = array(
   'property' => 'po:sameAs',
   'target' => 'po:Person',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
/* Residences */
$relationship_assignments['residences'][] = array(
   'property' => 'po:informationSource',
   'target' => 'po:InformationSource',
);
$relationship_assignments['residences'][] = array(
   'property' => 'po:livedInBy',
   'target' => 'po:Person',
);
$relationship_assignments['residences'][] = array(
   'property' => 'po:locatedIn',
   'target' => 'po:Location',
);
$relationship_assignments['residences'][] = array(
   'property' => 'po:sameAs',
   'target' => 'po:Residence',
);
$relationship_assignments['residences'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['residences'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
