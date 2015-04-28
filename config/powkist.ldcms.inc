<?php
/*
 * powkist.ldcms.inc
 * 
 * Copyright (c) 2011-2014, Hai Nguyen (hai.nguyen@abdn.ac.uk),
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
  'default_class' => 'pk:Subject',

  // Local identifier property and default prefix for new instances.
  'identifier_property' => 'pk:subjectID',
  'default_prefix' => 'pk',

  // Title and description properties for summary views etc.
  'title_property' => 'hc:title',
  'description_property' => 'hc:description',
    
  // Record metadata properties.
  'owner_property' => 'pk:ownedBySociety',
  'maintainer_property' => 'pk:maintainedBySociety',
  'published_property' => 'pk:approvedForPub',
  'editor_notes_property' => 'pk:editorNotes',

  // Image details for gallery displays.
  'image_class' => 'hc:ImageFile',
  'image_relationship_property' => 'hc:hasImageFile',
  'url_property' => 'hc:URL',

  // DateRange definition.
  'date_range_class' => 'pk:DateRange',
  'date_range_from' => 'pk:dateFrom',
  'date_range_to' => 'pk:dateTo',
  // Settings for map
  'map_settings' => array (
   // should be updated according to the property name defined below for coordinates
   'map_x_prop' =>'pk:latitude',
   'map_y_prop' =>'pk:longitude',
   // the map will appear after this field (choose the value of either 'map_x_prop' and 'map_y_prop')
   'map_position'=> 'pk:longitude',
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
  'property' => 'pk:dateFrom',
  'label'    => 'Date From',
  'type'     => 'datetime',
);
$fields[] = array(
  'property' => 'pk:dateTo',
  'label'    => 'Date To',
  'type'     => 'datetime',
);

/* auto generated from here*/

$namespaces = array(
	'dc' => 'http://purl.org/dc/terms/',
	'hc' => 'http://www.hebrideanconnections.com/hebridean.owl#',
	'pk' => 'http://www.curios.abdn.ac.uk/powkist.owl#',
	'owl' => 'http://www.w3.org/2002/07/owl#',
	'rdf' => 'http://www.w3.org/1999/02/22-rdf-syntax-ns#',
	'xml' => 'http://www.w3.org/XML/1998/namespace',
	'xsd' => 'http://www.w3.org/2001/XMLSchema#',
	'rdfs' => 'http://www.w3.org/2000/01/rdf-schema#',
);
$allrecords = array(
	'pk:HistoricalEvent',
	'pk:Location',
	'hc:ImageFile',
	'pk:Person',
	'pk:Diary',
	'pk:Resource',
	'pk:ObjectOrArtefact',
	'hc:SoundFile',
	'pk:DiaryEntry',
	'pk:Organisation',
	'pk:Camp',
	'pk:Correspondence',
);
$fields[] = array(
	'property' => 'pk:typeOfCorrespondence',
	'label'    => 'Type Of Correspondence',
	'type'     => 'autocomplete',
);
$fields[] = array(
	'property' => 'pk:rank',
	'label'    => 'Rank',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'hc:URL',
	'label'    => 'URL',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'pk:editorNotes',
	'label'    => 'Editor Notes',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'pk:easting',
	'label'    => 'Easting',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'pk:typeOfThing',
	'label'    => 'Type Of Thing',
	'type'     => 'autocomplete',
);
$fields[] = array(
	'property' => 'pk:fromExternal',
	'label'    => 'From External',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'pk:latitude',
	'label'    => 'Latitude',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'pk:approvedForPub',
	'label'    => 'Approved For Pub',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'pk:northing',
	'label'    => 'Northing',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'pk:country',
	'label'    => 'Country',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'pk:typeOfOrganisation',
	'label'    => 'Type Of Organisation',
	'type'     => 'autocomplete',
);
$fields[] = array(
	'property' => 'pk:maintainedBySociety',
	'label'    => 'Maintained By Society',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'hc:title',
	'label'    => 'Title',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'pk:typeOfObjectArtefact',
	'label'    => 'Type Of Object Artefact',
	'type'     => 'autocomplete',
);
$fields[] = array(
	'property' => 'hc:description',
	'label'    => 'Description',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'pk:typeOfEvent',
	'label'    => 'Type Of Event',
	'type'     => 'autocomplete',
);
$fields[] = array(
	'property' => 'pk:sex',
	'label'    => 'Sex',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'pk:ownedBySociety',
	'label'    => 'Owned By Society',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'pk:subjectID',
	'label'    => 'Subject ID',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'pk:longitude',
	'label'    => 'Longitude',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'pk:copyright',
	'label'    => 'Copyright',
	'type'     => 'text',
);
$fields[] = array(
	'property' => 'pk:typeOfResources',
	'label'    => 'Type Of Resources',
	'type'     => 'autocomplete',
);
$fields[] = array(
	'property' => 'pk:typeOfLocation',
	'label'    => 'Type Of Location',
	'type'     => 'autocomplete',
);
$fields[] = array(
	'property' => 'pk:dateWritten',
	'label'    => 'Date Written',
	'type'     => 'daterange',
);
$fields[] = array(
	'property' => 'pk:dateOfDeath',
	'label'    => 'Date Of Death',
	'type'     => 'daterange',
);
$fields[] = array(
	'property' => 'pk:date',
	'label'    => 'Date',
	'type'     => 'daterange',
);
$fields[] = array(
	'property' => 'pk:born',
	'label'    => 'Born',
	'type'     => 'daterange',
);
$fields[] = array(
	'property' => 'pk:writtenToDate',
	'label'    => 'Written To Date',
	'type'     => 'daterange',
);
$fields[] = array(
	'property' => 'pk:writtenFromDate',
	'label'    => 'Written From Date',
	'type'     => 'daterange',
);
$fields[] = array(
	'property' => 'pk:dateSent',
	'label'    => 'Date Sent',
	'type'     => 'daterange',
);
$fields[] = array(
	'property' => 'pk:dateLiberated',
	'label'    => 'Date Liberated',
	'type'     => 'daterange',
);
$fields[] = array(
	'property' => 'pk:dateOfSource',
	'label'    => 'Date Of Source',
	'type'     => 'daterange',
);
$fields[] = array(
	'property' => 'pk:dateOfMarriage',
	'label'    => 'Date Of Marriage',
	'type'     => 'daterange',
);
$fields[] = array(
	'property' => 'pk:dateOfRegistration',
	'label'    => 'Date Of Registration',
	'type'     => 'daterange',
);
$fields[] = array(
	'property' => 'pk:diedAt',
	'label'    => 'Died At',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:holds',
	'label'    => 'Holds',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:married',
	'label'    => 'Married',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:locationUsed',
	'label'    => 'Location Used',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:livedHere',
	'label'    => 'Lived Here',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:fromSource',
	'label'    => 'From Source',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:locationFrom',
	'label'    => 'Location From',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:heldBy',
	'label'    => 'Held By',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:internedHere',
	'label'    => 'Interned Here',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:movedFrom',
	'label'    => 'Moved From',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:locatedAt',
	'label'    => 'Located At',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:crewedBy',
	'label'    => 'Crewed By',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:writtenCompiledBy',
	'label'    => 'Written Compiled By',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:movedToHere',
	'label'    => 'Moved To Here',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:internedIn',
	'label'    => 'Interned In',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:owned',
	'label'    => 'Owned',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:isHeardHere',
	'label'    => 'Is Heard Here',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:hasEntry',
	'label'    => 'Has Entry',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:sourceOf',
	'label'    => 'Source Of',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:sourceOfInformationOn',
	'label'    => 'Source Of Information On',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:isEntryOf',
	'label'    => 'Is Entry Of',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:associatedWith',
	'label'    => 'Associated With',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:parentOf',
	'label'    => 'Parent Of',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:bornHere',
	'label'    => 'Born Here',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:foundHere',
	'label'    => 'Found Here',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:siblingOf',
	'label'    => 'Sibling Of',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:locatedNear',
	'label'    => 'Located Near',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:bornAt',
	'label'    => 'Born At',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'hc:hasSoundFile',
	'label'    => 'Has Sound File',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:isPartOfSite',
	'label'    => 'Is Part Of Site',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:isShownHere',
	'label'    => 'Is Shown Here',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'hc:hasImageFile',
	'label'    => 'Has Image File',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:movedTo',
	'label'    => 'Moved To',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:childOf',
	'label'    => 'Child Of',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:locationTaken',
	'label'    => 'Location Taken',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:locatedHere',
	'label'    => 'Located Here',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:authorCompilerOf',
	'label'    => 'Author Compiler Of',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:ownedBy',
	'label'    => 'Owned By',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:informationObtainedFrom',
	'label'    => 'Information Obtained From',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:foundAt',
	'label'    => 'Found At',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:locationTo',
	'label'    => 'Location To',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:livedAt',
	'label'    => 'Lived At',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:relatedTo',
	'label'    => 'Related To',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:livedWith',
	'label'    => 'Lived With',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:diedHere',
	'label'    => 'Died Here',
	'type'     => 'relationship',
);
$fields[] = array(
	'property' => 'pk:movedFromHere',
	'label'    => 'Moved From Here',
	'type'     => 'relationship',
);
$browsing_classes[] = array(
	'label'       => 'Historical Event',
	'name'        => 'historicalevent',
	'class'       => 'pk:HistoricalEvent',
	'title'       => 'hc:title',
	'description' => 'hc:description',
);
$browsing_classes[] = array(
	'label'       => 'Location',
	'name'        => 'location',
	'class'       => 'pk:Location',
	'title'       => 'hc:title',
	'description' => 'hc:description',
);
$browsing_classes[] = array(
	'label'       => 'Image File',
	'name'        => 'imagefile',
	'class'       => 'hc:ImageFile',
	'title'       => 'hc:title',
	'description' => 'hc:description',
);
$browsing_classes[] = array(
	'label'       => 'Person',
	'name'        => 'person',
	'class'       => 'pk:Person',
	'title'       => 'hc:title',
	'description' => 'hc:description',
);
$browsing_classes[] = array(
	'label'       => 'Diary',
	'name'        => 'diary',
	'class'       => 'pk:Diary',
	'title'       => 'hc:title',
	'description' => 'hc:description',
);
$browsing_classes[] = array(
	'label'       => 'Resource',
	'name'        => 'resource',
	'class'       => 'pk:Resource',
	'title'       => 'hc:title',
	'description' => 'hc:description',
);
$browsing_classes[] = array(
	'label'       => 'Subject',
	'name'        => 'subject',
	'class'       => 'pk:Subject',
	'title'       => 'hc:title',
	'description' => 'hc:description',
);
$browsing_classes[] = array(
	'label'       => 'Object Or Artefact',
	'name'        => 'objectorartefact',
	'class'       => 'pk:ObjectOrArtefact',
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
	'label'       => 'Diary Entry',
	'name'        => 'diaryentry',
	'class'       => 'pk:DiaryEntry',
	'title'       => 'hc:title',
	'description' => 'hc:description',
);
$browsing_classes[] = array(
	'label'       => 'Organisation',
	'name'        => 'organisation',
	'class'       => 'pk:Organisation',
	'title'       => 'hc:title',
	'description' => 'hc:description',
);
$browsing_classes[] = array(
	'label'       => 'Camp',
	'name'        => 'camp',
	'class'       => 'pk:Camp',
	'title'       => 'hc:title',
	'description' => 'hc:description',
);
$browsing_classes[] = array(
	'label'       => 'Correspondence',
	'name'        => 'correspondence',
	'class'       => 'pk:Correspondence',
	'title'       => 'hc:title',
	'description' => 'hc:description',
);
/* field assignment for HistoricalEvent */
$field_assignments['historicalevent'] = array(
	'pk:editorNotes',
	'pk:fromExternal',
	'pk:latitude',
	'pk:approvedForPub',
	'pk:maintainedBySociety',
	'hc:title',
	'hc:description',
	'pk:typeOfEvent',
	'pk:ownedBySociety',
	'pk:subjectID',
	'pk:longitude',
	'pk:date',
);
/* field assignment for Location */
$field_assignments['location'] = array(
	'pk:editorNotes',
	'pk:easting',
	'pk:fromExternal',
	'pk:latitude',
	'pk:approvedForPub',
	'pk:northing',
	'pk:country',
	'pk:maintainedBySociety',
	'hc:title',
	'hc:description',
	'pk:ownedBySociety',
	'pk:subjectID',
	'pk:longitude',
	'pk:typeOfLocation',
	'pk:date',
);
/* field assignment for ImageFile */
$field_assignments['imagefile'] = array(
	'hc:URL',
	'pk:editorNotes',
	'pk:fromExternal',
	'pk:approvedForPub',
	'pk:maintainedBySociety',
	'hc:title',
	'hc:description',
	'pk:ownedBySociety',
	'pk:subjectID',
	'pk:date',
);
/* field assignment for Person */
$field_assignments['person'] = array(
	'pk:rank',
	'pk:editorNotes',
	'pk:fromExternal',
	'pk:approvedForPub',
	'pk:country',
	'pk:maintainedBySociety',
	'hc:title',
	'hc:description',
	'pk:sex',
	'pk:ownedBySociety',
	'pk:subjectID',
	'pk:dateOfDeath',
	'pk:date',
	'pk:born',
	'pk:dateOfMarriage',
);
/* field assignment for Diary */
$field_assignments['diary'] = array(
	'pk:editorNotes',
	'pk:fromExternal',
	'pk:approvedForPub',
	'pk:maintainedBySociety',
	'hc:title',
	'hc:description',
	'pk:ownedBySociety',
	'pk:subjectID',
	'pk:date',
	'pk:writtenToDate',
	'pk:writtenFromDate',
);
/* field assignment for Resource */
$field_assignments['resource'] = array(
	'pk:editorNotes',
	'pk:fromExternal',
	'pk:approvedForPub',
	'pk:maintainedBySociety',
	'hc:title',
	'hc:description',
	'pk:ownedBySociety',
	'pk:subjectID',
	'pk:typeOfResources',
	'pk:date',
);
/* field assignment for DateRange */
/* field assignment for Subject */
$field_assignments['subject'] = array(
	'pk:typeOfCorrespondence',
	'pk:rank',
	'hc:URL',
	'pk:editorNotes',
	'pk:easting',
	'pk:dateTo',
	'pk:typeOfThing',
	'pk:fromExternal',
	'pk:latitude',
	'pk:approvedForPub',
	'pk:northing',
	'pk:country',
	'pk:dateFrom',
	'pk:typeOfOrganisation',
	'pk:maintainedBySociety',
	'hc:title',
	'pk:typeOfObjectArtefact',
	'hc:description',
	'pk:typeOfEvent',
	'pk:sex',
	'pk:ownedBySociety',
	'pk:subjectID',
	'pk:longitude',
	'pk:copyright',
	'pk:typeOfResources',
	'pk:typeOfLocation',
	'pk:dateWritten',
	'pk:dateOfDeath',
	'pk:date',
	'pk:born',
	'pk:writtenToDate',
	'pk:writtenFromDate',
	'pk:dateSent',
	'pk:dateLiberated',
	'pk:dateOfSource',
	'pk:dateOfMarriage',
	'pk:dateOfRegistration',
);
/* field assignment for ObjectOrArtefact */
$field_assignments['objectorartefact'] = array(
	'pk:editorNotes',
	'pk:fromExternal',
	'pk:approvedForPub',
	'pk:maintainedBySociety',
	'hc:title',
	'pk:typeOfObjectArtefact',
	'hc:description',
	'pk:ownedBySociety',
	'pk:subjectID',
	'pk:date',
);
/* field assignment for SoundFile */
$field_assignments['soundfile'] = array(
	'hc:URL',
	'pk:editorNotes',
	'pk:fromExternal',
	'pk:approvedForPub',
	'pk:maintainedBySociety',
	'hc:title',
	'hc:description',
	'pk:ownedBySociety',
	'pk:subjectID',
	'pk:date',
);
/* field assignment for DiaryEntry */
$field_assignments['diaryentry'] = array(
	'pk:editorNotes',
	'pk:fromExternal',
	'pk:latitude',
	'pk:approvedForPub',
	'pk:maintainedBySociety',
	'hc:title',
	'hc:description',
	'pk:ownedBySociety',
	'pk:subjectID',
	'pk:longitude',
	'pk:dateWritten',
	'pk:date',
);
/* field assignment for Organisation */
$field_assignments['organisation'] = array(
	'pk:editorNotes',
	'pk:fromExternal',
	'pk:approvedForPub',
	'pk:country',
	'pk:typeOfOrganisation',
	'pk:maintainedBySociety',
	'hc:title',
	'hc:description',
	'pk:ownedBySociety',
	'pk:subjectID',
	'pk:date',
);
/* field assignment for Camp */
$field_assignments['camp'] = array(
	'pk:editorNotes',
	'pk:fromExternal',
	'pk:latitude',
	'pk:approvedForPub',
	'pk:country',
	'pk:maintainedBySociety',
	'hc:title',
	'hc:description',
	'pk:ownedBySociety',
	'pk:subjectID',
	'pk:longitude',
	'pk:date',
	'pk:dateLiberated',
);
/* field assignment for Correspondence */
$field_assignments['correspondence'] = array(
	'pk:typeOfCorrespondence',
	'pk:editorNotes',
	'pk:fromExternal',
	'pk:approvedForPub',
	'pk:maintainedBySociety',
	'hc:title',
	'hc:description',
	'pk:ownedBySociety',
	'pk:subjectID',
	'pk:dateWritten',
	'pk:date',
	'pk:dateSent',
);
/* relationship for HistoricalEvent */
$relationship_assignments['historicalevent'][] = array(
	'property' => 'pk:associatedWith',
	'target'   => $allrecords,
);
$relationship_assignments['historicalevent'][] = array(
	'property' => 'hc:hasSoundFile',
	'target'   => 'hc:SoundFile',
);
$relationship_assignments['historicalevent'][] = array(
	'property' => 'hc:hasImageFile',
	'target'   => 'hc:ImageFile',
);
$relationship_assignments['historicalevent'][] = array(
	'property' => 'pk:informationObtainedFrom',
	'target'   => 'pk:Resource',
);
/* relationship for Location */
$relationship_assignments['location'][] = array(
	'property' => 'pk:movedToHere',
	'target'   => 'pk:Person',
);
$relationship_assignments['location'][] = array(
	'property' => 'pk:associatedWith',
	'target'   => $allrecords,
);
$relationship_assignments['location'][] = array(
	'property' => 'pk:bornHere',
	'target'   => 'pk:Person',
);
$relationship_assignments['location'][] = array(
	'property' => 'hc:hasSoundFile',
	'target'   => 'hc:SoundFile',
);
$relationship_assignments['location'][] = array(
	'property' => 'hc:hasImageFile',
	'target'   => 'hc:ImageFile',
);
$relationship_assignments['location'][] = array(
	'property' => 'pk:informationObtainedFrom',
	'target'   => 'pk:Resource',
);
$relationship_assignments['location'][] = array(
	'property' => 'pk:livedAt',
	'target'   => 'pk:Person',
);
$relationship_assignments['location'][] = array(
	'property' => 'pk:movedFromHere',
	'target'   => 'pk:Person',
);
/* relationship for ImageFile */
$relationship_assignments['imagefile'][] = array(
	'property' => 'pk:associatedWith',
	'target'   => $allrecords,
);
$relationship_assignments['imagefile'][] = array(
	'property' => 'hc:hasSoundFile',
	'target'   => 'hc:SoundFile',
);
$relationship_assignments['imagefile'][] = array(
	'property' => 'hc:hasImageFile',
	'target'   => 'hc:ImageFile',
);
$relationship_assignments['imagefile'][] = array(
	'property' => 'pk:locationTaken',
	'target'   => 'pk:Location',
);
$relationship_assignments['imagefile'][] = array(
	'property' => 'pk:informationObtainedFrom',
	'target'   => 'pk:Resource',
);
/* relationship for Person */
$relationship_assignments['person'][] = array(
	'property' => 'pk:diedAt',
	'target'   => 'pk:Location',
);
$relationship_assignments['person'][] = array(
	'property' => 'pk:married',
	'target'   => 'pk:Person',
);
$relationship_assignments['person'][] = array(
	'property' => 'pk:livedHere',
	'target'   => 'pk:Location',
);
$relationship_assignments['person'][] = array(
	'property' => 'pk:movedFrom',
	'target'   => 'pk:Location',
);
$relationship_assignments['person'][] = array(
	'property' => 'pk:internedIn',
	'target'   => 'pk:Camp',
);
$relationship_assignments['person'][] = array(
	'property' => 'pk:associatedWith',
	'target'   => $allrecords,
);
$relationship_assignments['person'][] = array(
	'property' => 'pk:parentOf',
	'target'   => 'pk:Person',
);
$relationship_assignments['person'][] = array(
	'property' => 'pk:siblingOf',
	'target'   => 'pk:Person',
);
$relationship_assignments['person'][] = array(
	'property' => 'pk:bornAt',
	'target'   => 'pk:Location',
);
$relationship_assignments['person'][] = array(
	'property' => 'hc:hasSoundFile',
	'target'   => 'hc:SoundFile',
);
$relationship_assignments['person'][] = array(
	'property' => 'hc:hasImageFile',
	'target'   => 'hc:ImageFile',
);
$relationship_assignments['person'][] = array(
	'property' => 'pk:movedTo',
	'target'   => 'pk:Location',
);
$relationship_assignments['person'][] = array(
	'property' => 'pk:childOf',
	'target'   => 'pk:Person',
);
$relationship_assignments['person'][] = array(
	'property' => 'pk:authorCompilerOf',
	'target'   => 'pk:ObjectOrArtefact>, <http://www.curios.abdn.ac.uk/powkist.owl',
);
$relationship_assignments['person'][] = array(
	'property' => 'pk:informationObtainedFrom',
	'target'   => 'pk:Resource',
);
$relationship_assignments['person'][] = array(
	'property' => 'pk:relatedTo',
	'target'   => 'pk:Person',
);
$relationship_assignments['person'][] = array(
	'property' => 'pk:livedWith',
	'target'   => 'pk:Person',
);
/* relationship for Diary */
$relationship_assignments['diary'][] = array(
	'property' => 'pk:writtenCompiledBy',
	'target'   => 'pk:Person',
);
$relationship_assignments['diary'][] = array(
	'property' => 'pk:hasEntry',
	'target'   => 'pk:DiaryEntry',
);
$relationship_assignments['diary'][] = array(
	'property' => 'pk:associatedWith',
	'target'   => $allrecords,
);
$relationship_assignments['diary'][] = array(
	'property' => 'hc:hasSoundFile',
	'target'   => 'hc:SoundFile',
);
$relationship_assignments['diary'][] = array(
	'property' => 'hc:hasImageFile',
	'target'   => 'hc:ImageFile',
);
$relationship_assignments['diary'][] = array(
	'property' => 'pk:informationObtainedFrom',
	'target'   => 'pk:Resource',
);
/* relationship for Resource */
$relationship_assignments['resource'][] = array(
	'property' => 'pk:writtenCompiledBy',
	'target'   => 'pk:Person',
);
$relationship_assignments['resource'][] = array(
	'property' => 'pk:associatedWith',
	'target'   => $allrecords,
);
$relationship_assignments['resource'][] = array(
	'property' => 'hc:hasSoundFile',
	'target'   => 'hc:SoundFile',
);
$relationship_assignments['resource'][] = array(
	'property' => 'hc:hasImageFile',
	'target'   => 'hc:ImageFile',
);
/* relationship for Subject */
$relationship_assignments['subject'][] = array(
	'property' => 'pk:associatedWith',
	'target'   => $allrecords,
);
$relationship_assignments['subject'][] = array(
	'property' => 'hc:hasSoundFile',
	'target'   => 'hc:SoundFile',
);
$relationship_assignments['subject'][] = array(
	'property' => 'hc:hasImageFile',
	'target'   => 'hc:ImageFile',
);
/* relationship for ObjectOrArtefact */
$relationship_assignments['objectorartefact'][] = array(
	'property' => 'pk:locationUsed',
	'target'   => 'pk:Location',
);
$relationship_assignments['objectorartefact'][] = array(
	'property' => 'pk:writtenCompiledBy',
	'target'   => 'pk:Person',
);
$relationship_assignments['objectorartefact'][] = array(
	'property' => 'pk:associatedWith',
	'target'   => $allrecords,
);
$relationship_assignments['objectorartefact'][] = array(
	'property' => 'hc:hasSoundFile',
	'target'   => 'hc:SoundFile',
);
$relationship_assignments['objectorartefact'][] = array(
	'property' => 'hc:hasImageFile',
	'target'   => 'hc:ImageFile',
);
$relationship_assignments['objectorartefact'][] = array(
	'property' => 'pk:informationObtainedFrom',
	'target'   => 'pk:Resource',
);
$relationship_assignments['objectorartefact'][] = array(
	'property' => 'pk:foundAt',
	'target'   => 'pk:Location',
);
/* relationship for SoundFile */
$relationship_assignments['soundfile'][] = array(
	'property' => 'pk:associatedWith',
	'target'   => $allrecords,
);
$relationship_assignments['soundfile'][] = array(
	'property' => 'hc:hasSoundFile',
	'target'   => 'hc:SoundFile',
);
$relationship_assignments['soundfile'][] = array(
	'property' => 'hc:hasImageFile',
	'target'   => 'hc:ImageFile',
);
$relationship_assignments['soundfile'][] = array(
	'property' => 'pk:informationObtainedFrom',
	'target'   => 'pk:Resource',
);
/* relationship for DiaryEntry */
$relationship_assignments['diaryentry'][] = array(
	'property' => 'pk:locatedAt',
	'target'   => 'pk:Location',
);
$relationship_assignments['diaryentry'][] = array(
	'property' => 'pk:isEntryOf',
	'target'   => 'pk:Diary',
);
$relationship_assignments['diaryentry'][] = array(
	'property' => 'pk:associatedWith',
	'target'   => $allrecords,
);
$relationship_assignments['diaryentry'][] = array(
	'property' => 'hc:hasSoundFile',
	'target'   => 'hc:SoundFile',
);
$relationship_assignments['diaryentry'][] = array(
	'property' => 'hc:hasImageFile',
	'target'   => 'hc:ImageFile',
);
$relationship_assignments['diaryentry'][] = array(
	'property' => 'pk:informationObtainedFrom',
	'target'   => 'pk:Resource',
);
/* relationship for Organisation */
$relationship_assignments['organisation'][] = array(
	'property' => 'pk:holds',
	'target'   => 'pk:Resource',
);
$relationship_assignments['organisation'][] = array(
	'property' => 'pk:associatedWith',
	'target'   => $allrecords,
);
$relationship_assignments['organisation'][] = array(
	'property' => 'hc:hasSoundFile',
	'target'   => 'hc:SoundFile',
);
$relationship_assignments['organisation'][] = array(
	'property' => 'hc:hasImageFile',
	'target'   => 'hc:ImageFile',
);
$relationship_assignments['organisation'][] = array(
	'property' => 'pk:informationObtainedFrom',
	'target'   => 'pk:Resource',
);
/* relationship for Camp */
$relationship_assignments['camp'][] = array(
	'property' => 'pk:internedHere',
	'target'   => 'pk:Person',
);
$relationship_assignments['camp'][] = array(
	'property' => 'pk:locatedAt',
	'target'   => 'pk:Location',
);
$relationship_assignments['camp'][] = array(
	'property' => 'pk:associatedWith',
	'target'   => $allrecords,
);
$relationship_assignments['camp'][] = array(
	'property' => 'hc:hasSoundFile',
	'target'   => 'hc:SoundFile',
);
$relationship_assignments['camp'][] = array(
	'property' => 'hc:hasImageFile',
	'target'   => 'hc:ImageFile',
);
$relationship_assignments['camp'][] = array(
	'property' => 'pk:informationObtainedFrom',
	'target'   => 'pk:Resource',
);
/* relationship for Correspondence */
$relationship_assignments['correspondence'][] = array(
	'property' => 'pk:locationFrom',
	'target'   => 'pk:Location',
);
$relationship_assignments['correspondence'][] = array(
	'property' => 'pk:writtenCompiledBy',
	'target'   => 'pk:Person',
);
$relationship_assignments['correspondence'][] = array(
	'property' => 'pk:associatedWith',
	'target'   => $allrecords,
);
$relationship_assignments['correspondence'][] = array(
	'property' => 'hc:hasSoundFile',
	'target'   => 'hc:SoundFile',
);
$relationship_assignments['correspondence'][] = array(
	'property' => 'hc:hasImageFile',
	'target'   => 'hc:ImageFile',
);
$relationship_assignments['correspondence'][] = array(
	'property' => 'pk:informationObtainedFrom',
	'target'   => 'pk:Resource',
);
$relationship_assignments['correspondence'][] = array(
	'property' => 'pk:locationTo',
	'target'   => 'pk:Location',
);
