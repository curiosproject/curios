<?php
/*
 * hebridean.ldcms.inc
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

$namespaces = array(
  'hc' => 'http://www.hebrideanconnections.com/hebridean.owl#',
  'dc' => 'http://purl.org/dc/terms/',
);

$options = array(
  // Default/fallback class - is a super class of all base classes.
  'default_class' => 'hc:Subject',

  // Local identifier property and default prefix for new instances.
  'identifier_property' => 'hc:subjectID',
  'default_prefix' => 'hc',

  // Title and description properties for summary views etc.
  'title_property' => 'hc:title',
  'description_property' => 'hc:description',
    
  // Record metadata properties.
  'owner_property' => //'hc:ownedBySociety',
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
  'label'    => 'dc:title',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'dc:description',
  'label'    => 'dc:description',
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

$all_records = array(
    'hc:LandmarkOrArchaeologicalSite',
    'hc:Business',
    'hc:HistoricalEvent',
    'hc:Location',
    'hc:GaelicVersebRdachd',
    'hc:ObjectOrArtefact',
    'hc:NaturalLandscapeFeature',
    'hc:StoryReportOrTradition',
    'hc:Boat',
    'hc:Person',
    'hc:CroftOrResidence',
    'hc:Organisation',
    'hc:Person',
    'hc:BuildingOrPublicAmenity',
    'hc:Resource',
    'hc:Vehicle',
);


/* FILE IS AUTO GENERATED FROM HERE ON */
/* Literal Value Fields */

$fields[] = array(
   'property' => 'hc:sex',
   'label'    => 'Sex',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:born',
   'label'    => 'Date of Birth',
   'type'     => 'daterange',
);
$fields[] = array(
   'property' => 'hc:dateOfDeath',
   'label'    => 'Date of Death',
   'type'     => 'daterange',
);
$fields[] = array(
   'property' => 'hc:typeOfSite',
   'label'    => 'Type',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:typeOfObjectArtefact',
   'label'    => 'Type',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:occupation',
   'label'    => 'Occupation',
   'type'     => 'autocomplete_multival',
);
$fields[] = array(
   'property' => 'hc:dateFounded',
   'label'    => 'Date Founded',
   'type'     => 'daterange',
);
$fields[] = array(
   'property' => 'hc:typeOfLocation',
   'label'    => 'Type',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:timePeriod',
   'label'    => 'Time Period',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:typeOfBusiness',
   'label'    => 'Type',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:typeOfResidence',
   'label'    => 'Type',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:typeOfNaturalLandscapeFeature',
   'label'    => 'Type',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:typeOfStoryReportTradition',
   'label'    => 'Type',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:dateOfMarriage',
   'label'    => 'Date of Marriage',
   'type'     => 'daterange',
);
$fields[] = array(
   'property' => 'hc:bkReference',
   'label'    => 'Bk Reference',
   'type'     => 'text_multival',
);
$fields[] = array(
   'property' => 'hc:dateBuilt',
   'label'    => 'Date Built',
   'type'     => 'daterange',
);
$fields[] = array(
   'property' => 'hc:dateEstablished',
   'label'    => 'Date Established',
   'type'     => 'daterange',
);
$fields[] = array(
   'property' => 'hc:typeOfBuildingPublicAmenity',
   'label'    => 'Type',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:typeOfOrganisation',
   'label'    => 'Type',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:periodOfConstructionUse',
   'label'    => 'Period of Construction',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:sourceType',
   'label'    => 'Source Type',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'hc:dateOfSource',
   'label'    => 'Date of Source',
   'type'     => 'daterange',
);
$fields[] = array(
   'property' => 'hc:dateOfRegistration',
   'label'    => 'Date of Registration',
   'type'     => 'daterange',
);
$fields[] = array(
   'property' => 'hc:typeOfBoat',
   'label'    => 'Type',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:dateLaunched',
   'label'    => 'Date Launched',
   'type'     => 'daterange',
);
$fields[] = array(
   'property' => 'hc:typeOfVehicle',
   'label'    => 'Type',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:typeOfEvent',
   'label'    => 'Type',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:dateLotted',
   'label'    => 'Date Lotted',
   'type'     => 'daterange',
);
$fields[] = array(
   'property' => 'hc:chassis',
   'label'    => 'Chassis',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'hc:theme',
   'label'    => 'Theme',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:SMRRecordID',
   'label'    => 'SMR Record ID',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'hc:alsoKnownAs',
   'label'    => 'Also Known As',
   'type'     => 'text_multival',
);
$fields[] = array(
   'property' => 'hc:date',
   'label'    => 'Date',
   'type'     => 'daterange',
);
$fields[] = array(
   'property' => 'hc:period',
   'label'    => 'Period',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:registration',
   'label'    => 'Registration',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'hc:easting',
   'label'    => 'Grid Ref Easting',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'hc:northing',
   'label'    => 'Grid Ref Northing',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'hc:subjectID',
   'label'    => 'Subject Id',
   'type'     => 'integer',
);
$fields[] = array(
   'property' => //'hc:ownedBySociety',
   'label'    => 'Record Owned By',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:approvedForPub',
   'label'    => 'Published',
   'type'     => 'autocomplete',
);
$fields[] = array(
   'property' => 'hc:title',
   'label'    => 'English Name',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'hc:gaelicName',
   'label'    => 'Gaelic Name',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'hc:maintainedBySociety',
   'label'    => 'Record Maintained By',
   'type'     => 'autocomplete_multival',
);
$fields[] = array(
   'property' => 'hc:description',
   'label'    => 'Description',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'hc:title',
   'label'    => 'Title',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'hc:URL',
   'label'    => 'URL',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'hc:fileName',
   'label'    => 'Filename',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'hc:copyright',
   'label'    => 'Copyright',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'hc:originator',
   'label'    => 'Originator',
   'type'     => 'text',
);
$fields[] = array(
   'property' => 'hc:originDate',
   'label'    => 'Date',
   'type'     => 'daterange',
);
$fields[] = array(
   'property' => 'hc:editorNotes',
   'label'    => 'Editor notes',
   'type'     => 'text',
);

/* Relationship Fields */

$fields[] = array(
   'property' => 'hc:siblingOf',
   'label'    => 'Sibling Of',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:parentOf',
   'label'    => 'Parent Of',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:childOf',
   'label'    => 'Child Of',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:married',
   'label'    => 'Married',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:relatedTo',
   'label'    => 'Related To',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:crewedBy',
   'label'    => 'Crewed By',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:onCrewOfBoat',
   'label'    => 'On Crew Of Boat',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:movedFrom',
   'label'    => 'Moved From',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:movedTo',
   'label'    => 'Moved To',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:dateDemolished',
   'label'    => 'Date Demolished',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:immigrantFrom',
   'label'    => 'Immigrant From',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:emigratedTo',
   'label'    => 'Emigrated To',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:livedWith',
   'label'    => 'Lived With',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:adopterOf',
   'label'    => 'Adopter Of',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:adoptedBy',
   'label'    => 'Adopted By',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:fostererOf',
   'label'    => 'Fosterer Of',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:fosteredBy',
   'label'    => 'Fostered By',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:usedObject',
   'label'    => 'Used Object',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:bornAt',
   'label'    => 'Born At',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:bornHere',
   'label'    => 'Born Here',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:diedAt',
   'label'    => 'Died At',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:diedHere',
   'label'    => 'Died Here',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:compiledBy',
   'label'    => 'Compiled By Organisation',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:compilerOf',
   'label'    => 'Compiler Of',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:isPartOfSite',
   'label'    => 'Is Part Of Site',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:includesSubSite',
   'label'    => 'Includes Sub Site',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:builtBy',
   'label'    => 'Built By',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:builderOfBoat',
   'label'    => 'Builder Of Boat',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:holds',
   'label'    => 'Holds',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:writtenCompiledBy',
   'label'    => 'Written By Person',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:authorCompilerOf',
   'label'    => 'Author Compiler Of',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:mayBeTheSameAs',
   'label'    => 'May Be The Same As',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:composedBy',
   'label'    => 'Composed By',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:composedSong',
   'label'    => 'Composed Song',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:immigratedHere',
   'label'    => 'Immigrated Here',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:heldBy',
   'label'    => 'Held By',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:emigratedFromHere',
   'label'    => 'Emigrated From Here',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:movedFromHere',
   'label'    => 'Moved From Here',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:movedToHere',
   'label'    => 'Moved To Here',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:associatedWith',
   'label'    => 'Associated With',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:owned',
   'label'    => 'Owned',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:ownedBy',
   'label'    => 'Owned By',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:locatedAt',
   'label'    => 'Located At',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:locatedHere',
   'label'    => 'Located Here',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:employed',
   'label'    => 'Employed',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:employedBy',
   'label'    => 'Employed By',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:foundHere',
   'label'    => 'Found Here',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:foundAt',
   'label'    => 'Found At',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:geoRef',
   'label'    => 'Geo Ref',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:informationObtainedFrom',
   'label'    => 'Information Obtained From',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:sourceOfInformationOn',
   'label'    => 'Source Of Information On',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:livedAt',
   'label'    => 'Lived At',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:livedHere',
   'label'    => 'Lived Here',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:locatedNear',
   'label'    => 'Located Near',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:hasImageFile',
   'label'    => 'Has Image File',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:hasSoundFile',
   'label'    => 'Has Sound File',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:isShownHere',
   'label'    => 'Associated With',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:isHeardHere',
   'label'    => 'Associated With',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:sourceOf',
   'label'    => 'Source Of',
   'type'     => 'relationship',
);
$fields[] = array(
   'property' => 'hc:fromSource',
   'label'    => 'From Person',
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
   'name'  => 'boats',
   'label' => 'Boats',
   'class' => 'hc:Boat',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'buildings_and_public_amenities',
   'label' => 'Buildings and Public Amenities',
   'class' => 'hc:BuildingOrPublicAmenity',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'businesses',
   'label' => 'Businesses',
   'class' => 'hc:Business',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'crofts_and_residences',
   'label' => 'Crofts and Residences',
   'class' => 'hc:CroftOrResidence',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'gaelic_verse',
   'label' => 'Gaelic Verse',
   'class' => 'hc:GaelicVerse',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'historical_events',
   'label' => 'Historical Events',
   'class' => 'hc:HistoricalEvent',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'landmarks_and_archaeological_sites',
   'label' => 'Historical/ Archaeological Sites',
   'class' => 'hc:LandmarkOrArchaeologicalSite',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'locations',
   'label' => 'Locations',
   'class' => 'hc:Location',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'natural_landscape_features',
   'label' => 'Natural Landscape Features',
   'class' => 'hc:NaturalLandscapeFeature',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'objects_and_artefacts',
   'label' => 'Objects and Artefacts',
   'class' => 'hc:ObjectOrArtefact',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'organisations',
   'label' => 'Organisations',
   'class' => 'hc:Organisation',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'people',
   'label' => 'People',
   'class' => 'hc:Person',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'resources',
   'label' => 'Resources',
   'class' => 'hc:Resource',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'stories_reports_and_traditions',
   'label' => 'Stories, Reports and Traditions',
   'class' => 'hc:StoryReportOrTradition',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'vehicles',
   'label' => 'Vehicles',
   'class' => 'hc:Vehicle',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'image_details',
   'label' => 'Image Details',
   'class' => 'hc:ImageFile',
   'title' => 'hc:title',
   'description' => 'hc:description',
);
$browsing_classes[] = array(
   'name'  => 'sound_files',
   'label' => 'Sound Files',
   'class' => 'hc:SoundFile',
   'title' => 'hc:title',
   'description' => 'hc:description',
);

/* Field Assignments */

$field_assignments['subjects'] = array(
   'hc:title',
   'hc:gaelicName',
   'hc:alsoKnownAs',
/*   'hc:typeOfBoat',
   'hc:typeOfBuildingPublicAmenity',
   'hc:typeOfBusiness',
   'hc:typeOfResidence',
   'hc:typeOfEvent',
   'hc:typeOfSite',
   'hc:typeOfLocation',
   'hc:typeOfNaturalLandscapeFeature',
   'hc:typeOfObjectArtefact',
   'hc:typeOfOrganisation',
   'hc:typeOfStoryReportTradition',
   'hc:typeOfVehicle',
*/
   'hc:dateLaunched',
   'hc:dateOfRegistration',
   'hc:registration',
//'hc:ownedBySociety',
   'hc:dateBuilt',
   'hc:dateEstablished',
   'hc:dateFounded',
   'hc:period',
   'hc:periodOfConstructionUse',
   'hc:SMRRecordID',
   'hc:northing',
   'hc:easting',
   'hc:geoRef',
   'hc:dateDemolished',
   'hc:dateLotted',
   'hc:date',
   'hc:theme',
   'hc:timePeriod',
   'hc:dateOfSource',
   'hc:born',
   'hc:dateOfDeath',
   'hc:dateOfMarriage',
   'hc:occupation',
   'hc:sex',
   'hc:bkReference',
   'hc:chassis',
   'hc:approvedForPub',
   'hc:copyright',
   'hc:description',
   'hc:fileName',
   'hc:maintainedBySociety',
   'hc:sourceType',
   'hc:subjectID',
   'hc:URL',
   'hc:originator',
   'hc:originDate',
   'hc:editorNotes',
);
$field_assignments['boats'] = array(
   'hc:title',
   'hc:gaelicName',
   'hc:alsoKnownAs',
//    'hc:typeOfBoat',
   'hc:dateLaunched',
   'hc:dateOfRegistration',
   'hc:registration',
//'hc:ownedBySociety',
   'hc:approvedForPub',
   'hc:description',
   'hc:maintainedBySociety',
   'hc:subjectID',
   'hc:editorNotes',
);
$field_assignments['buildings_and_public_amenities'] = array(
   'hc:title',
   'hc:gaelicName',
//   'hc:typeOfBuildingPublicAmenity',
//'hc:ownedBySociety',
   'hc:dateBuilt',
   'hc:periodOfConstructionUse',
   'hc:northing',
   'hc:easting',
   'hc:approvedForPub',
   'hc:description',
   'hc:maintainedBySociety',
   'hc:subjectID',
   'hc:editorNotes',
);
$field_assignments['businesses'] = array(
   'hc:title',
   'hc:gaelicName',
//    'hc:typeOfBusiness',
//'hc:ownedBySociety',
   'hc:dateFounded',
   'hc:northing',
   'hc:easting',
   'hc:approvedForPub',
   'hc:description',
   'hc:maintainedBySociety',
   'hc:subjectID',
   'hc:title',
   'hc:editorNotes',
);
$field_assignments['crofts_and_residences'] = array(
   'hc:title',
   'hc:gaelicName',
   'hc:typeOfResidence',
//'hc:ownedBySociety',
   'hc:dateBuilt',
   'hc:periodOfConstructionUse',
   'hc:northing',
   'hc:easting',
   'hc:dateLotted',
   'hc:approvedForPub',
   'hc:description',
   'hc:maintainedBySociety',
   'hc:subjectID',
   'hc:editorNotes',
);
$field_assignments['gaelic_verse'] = array(
   'hc:title',
   'hc:gaelicName',
//'hc:ownedBySociety',
   'hc:date',
   'hc:theme',
   'hc:approvedForPub',
   'hc:description',
   'hc:maintainedBySociety',
   'hc:subjectID',
   'hc:editorNotes',
);
$field_assignments['historical_events'] = array(
   'hc:title',
   'hc:gaelicName',
//    'hc:typeOfEvent',
//'hc:ownedBySociety',
   'hc:date',
   'hc:timePeriod',
   'hc:approvedForPub',
   'hc:description',
   'hc:maintainedBySociety',
   'hc:subjectID',
   'hc:editorNotes',
);
$field_assignments['landmarks_and_archaeological_sites'] = array(
   'hc:title',
   'hc:gaelicName',
//    'hc:typeOfSite',
//'hc:ownedBySociety',
   'hc:period',
   'hc:SMRRecordID',
   'hc:northing',
   'hc:easting',
   'hc:approvedForPub',
   'hc:description',
   'hc:maintainedBySociety',
   'hc:subjectID',
   'hc:editorNotes',
);
$field_assignments['locations'] = array(
   'hc:title',
   'hc:gaelicName',
   'hc:alsoKnownAs',
   'hc:typeOfLocation',
//'hc:ownedBySociety',
   'hc:northing',
   'hc:easting',
   'hc:approvedForPub',
   'hc:description',
   'hc:maintainedBySociety',
   'hc:subjectID',
   'hc:title',
   'hc:editorNotes',
);
$field_assignments['natural_landscape_features'] = array(
   'hc:title',
   'hc:gaelicName',
   'hc:alsoKnownAs',
//    'hc:typeOfNaturalLandscapeFeature',
//'hc:ownedBySociety',
   'hc:northing',
   'hc:easting',
   'hc:approvedForPub',
   'hc:description',
   'hc:maintainedBySociety',
   'hc:subjectID',
   'hc:editorNotes',
);
$field_assignments['objects_and_artefacts'] = array(
   'hc:title',
   'hc:gaelicName',
//    'hc:typeOfObjectArtefact',
//'hc:ownedBySociety',
   'hc:period',
   'hc:SMRRecordID',
   'hc:approvedForPub',
   'hc:description',
   'hc:maintainedBySociety',
   'hc:subjectID',
   'hc:title',
   'hc:editorNotes',
);
$field_assignments['organisations'] = array(
   'hc:title',
   'hc:gaelicName',
//    'hc:typeOfOrganisation',
//'hc:ownedBySociety',
   'hc:dateEstablished',
   'hc:approvedForPub',
   'hc:description',
   'hc:maintainedBySociety',
   'hc:subjectID',
   'hc:editorNotes',
);
$field_assignments['people'] = array(
   'hc:title',
   'hc:gaelicName',
   'hc:alsoKnownAs',
//'hc:ownedBySociety',
   'hc:born',
   'hc:dateOfDeath',
   'hc:dateOfMarriage',
   'hc:occupation',
   'hc:sex',
   'hc:bkReference',
   'hc:approvedForPub',
   'hc:description',
   'hc:maintainedBySociety',
   'hc:subjectID',
   'hc:editorNotes',
);
$field_assignments['resources'] = array(
   'hc:title',
   'hc:gaelicName',
//'hc:ownedBySociety',
   'hc:dateOfSource',
   'hc:approvedForPub',
   'hc:description',
   'hc:maintainedBySociety',
   'hc:sourceType',
   'hc:subjectID',
   'hc:editorNotes',
);
$field_assignments['stories_reports_and_traditions'] = array(
   'hc:title',
   'hc:gaelicName',
//    'hc:typeOfStoryReportTradition',
//'hc:ownedBySociety',
   'hc:date',
   'hc:approvedForPub',
   'hc:description',
   'hc:maintainedBySociety',
   'hc:subjectID',
   'hc:editorNotes',
);
$field_assignments['vehicles'] = array(
   'hc:title',
   'hc:gaelicName',
//    'hc:typeOfVehicle',
   'hc:registration',
//'hc:ownedBySociety',
   'hc:chassis',
   'hc:approvedForPub',
   'hc:description',
   'hc:maintainedBySociety',
   'hc:subjectID',
   'hc:editorNotes',
);
$field_assignments['image_details'] = array(
//'hc:ownedBySociety',
   'hc:approvedForPub',
   'hc:copyright',
   'hc:description',
   'hc:fileName',
   'hc:maintainedBySociety',
   'hc:subjectID',
   'hc:title',
   'hc:URL',
   'hc:originator',
   'hc:originDate',
   'hc:editorNotes',
);
$field_assignments['sound_files'] = array(
//'hc:ownedBySociety',
   'hc:approvedForPub',
   'hc:copyright',
   'hc:description',
   'hc:fileName',
   'hc:maintainedBySociety',
   'hc:subjectID',
   'hc:title',
   'hc:URL',
   'hc:originator',
   'hc:originDate',
   'hc:editorNotes',
);

/* Relationship Assignments */

/* Subjects */

$relationship_assignments['subjects'][] = array(
   'property' => 'hc:siblingOf',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:parentOf',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:childOf',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:married',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:relatedTo',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:crewedBy',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:onCrewOfBoat',
   'target' => 'hc:Boat',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:movedFrom',
   'target' => 'hc:Location',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:movedTo',
   'target' => 'hc:Location',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:immigrantFrom',
   'target' => 'hc:Location',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:emigratedTo',
   'target' => 'hc:Location',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:livedWith',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:adopterOf',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:adoptedBy',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:fostererOf',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:fosteredBy',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:usedObject',
   'target' => 'hc:ObjectOrArtefact',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:bornAt',
   'target' => 'hc:Location',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:bornHere',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:diedAt',
   'target' => 'hc:Location',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:diedHere',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:compiledBy',
   'target' => 'hc:Organisation',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:compilerOf',
   'target' => 'hc:Resource',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:isPartOfSite',
   'target' => 'hc:LandmarkOrArchaeologicalSite',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:includesSubSite',
   'target' => 'hc:LandmarkOrArchaeologicalSite',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:builtBy',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:builderOfBoat',
   'target' => 'hc:Boat',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:holds',
   'target' => array(
      'hc:ObjectOrArtefact',
      'hc:Resource',
   ),
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:writtenCompiledBy',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:authorCompilerOf',
   'target' => 'hc:Resource',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:mayBeTheSameAs',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:composedBy',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:composedSong',
   'target' => 'hc:GaelicVerse',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:immigratedHere',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:heldBy',
   'target' => 'hc:Organisation',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:emigratedFromHere',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:movedFromHere',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:movedToHere',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:fromSource',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:isHeardHere',
   'target' => $all_records,
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:isShownHere',
   'target' => $all_records,
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:employedBy',
   'target' => array(
      'hc:Business',
      'hc:Person',
   ),
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:foundHere',
   'target' => 'hc:ObjectOrArtefact',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:foundAt',
   'target' => array(
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
   ),
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:informationObtainedFrom',
   'target' => 'hc:Resource',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:sourceOfInformationOn',
   'target' => array(
      'hc:Boat',
      'hc:BuildingOrPublicAmenity',
      'hc:Business',
      'hc:CroftOrResidence',
      'hc:GaelicVerse',
      'hc:HistoricalEvent',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
      'hc:ObjectOrArtefact',
      'hc:Organisation',
      'hc:Person',
      'hc:StoryReportOrTradition',
      'hc:Vehicle',
   ),
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:livedAt',
   'target' => array(
      'hc:CroftOrResidence',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
   ),
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:livedHere',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:locatedNear',
   'target' => array(
      'hc:Location',
      'hc:NaturalLandscapeFeature',
   ),
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:associatedWith',
   'target' => array(
      'hc:Boat',
      'hc:BuildingOrPublicAmenity',
      'hc:Business',
      'hc:CroftOrResidence',
      'hc:GaelicVerse',
      'hc:HistoricalEvent',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
      'hc:ObjectOrArtefact',
      'hc:Organisation',
      'hc:Person',
      'hc:Resource',
      'hc:StoryReportOrTradition',
      'hc:Vehicle',
   ),
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:owned',
   'target' => array(
      'hc:Boat',
      'hc:Business',
      'hc:Vehicle',
   ),
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:ownedBy',
   'target' => array(
      'hc:Business',
      'hc:Person',
   ),
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:locatedAt',
   'target' => array(
      'hc:BuildingOrPublicAmenity',
      'hc:CroftOrResidence',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
   ),
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:locatedHere',
   'target' => array(
      'hc:BuildingOrPublicAmenity',
      'hc:Business',
      'hc:CroftOrResidence',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
      'hc:ObjectOrArtefact',
      'hc:Resource',
   ),
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:employed',
   'target' => 'hc:Person',
);
$relationship_assignments['subjects'][] = array(
   'property' => 'hc:sourceOf',
   'target' => 'hc:StoryReportOrTradition',
);

/* Boats */
$relationship_assignments['boats'][] = array(
   'property' => 'hc:crewedBy',
   'target' => 'hc:Person',
);
$relationship_assignments['boats'][] = array(
   'property' => 'hc:builtBy',
   'target' => 'hc:Person',
);
$relationship_assignments['boats'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['boats'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
$relationship_assignments['boats'][] = array(
   'property' => 'hc:informationObtainedFrom',
   'target' => 'hc:Resource',
);
$relationship_assignments['boats'][] = array(
   'property' => 'hc:associatedWith',
   'target' => array(
      'hc:Boat',
      'hc:Business',
      'hc:CroftOrResidence',
      'hc:GaelicVerse',
      'hc:HistoricalEvent',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
      'hc:ObjectOrArtefact',
      'hc:Organisation',
      'hc:Person',
      'hc:StoryReportOrTradition',
   ),
);
$relationship_assignments['boats'][] = array(
   'property' => 'hc:ownedBy',
   'target' => array(
      'hc:Business',
      'hc:Person',
   ),
);

/* Buildings and Public Amenities */
$relationship_assignments['buildings_and_public_amenities'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['buildings_and_public_amenities'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
$relationship_assignments['buildings_and_public_amenities'][] = array(
   'property' => 'hc:informationObtainedFrom',
   'target' => 'hc:Resource',
);
$relationship_assignments['buildings_and_public_amenities'][] = array(
   'property' => 'hc:associatedWith',
   'target' => array(
      'hc:BuildingOrPublicAmenity',
      'hc:Business',
      'hc:CroftOrResidence',
      'hc:GaelicVerse',
      'hc:HistoricalEvent',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
      'hc:ObjectOrArtefact',
      'hc:Organisation',
      'hc:Person',
      'hc:StoryReportOrTradition',
   ),
);
$relationship_assignments['buildings_and_public_amenities'][] = array(
   'property' => 'hc:locatedAt',
   'target' => array(
      'hc:CroftOrResidence',
      'hc:Location',
   ),
);
$relationship_assignments['buildings_and_public_amenities'][] = array(
   'property' => 'hc:locatedHere',
   'target' => array(
      'hc:Business',
      'hc:ObjectOrArtefact',
      'hc:Resource',
   ),
);

/* Businesses */
$relationship_assignments['businesses'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['businesses'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
$relationship_assignments['businesses'][] = array(
   'property' => 'hc:informationObtainedFrom',
   'target' => 'hc:Resource',
);
$relationship_assignments['businesses'][] = array(
   'property' => 'hc:associatedWith',
   'target' => array(
      'hc:Boat',
      'hc:BuildingOrPublicAmenity',
      'hc:Business',
      'hc:Business',
      'hc:CroftOrResidence',
      'hc:GaelicVerse',
      'hc:HistoricalEvent',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
      'hc:ObjectOrArtefact',
      'hc:Organisation',
      'hc:Person',
      'hc:StoryReportOrTradition',
      'hc:Vehicle',
   ),
);
$relationship_assignments['businesses'][] = array(
   'property' => 'hc:owned',
   'target' => array(
      'hc:Boat',
      'hc:Vehicle',
   ),
);
$relationship_assignments['businesses'][] = array(
   'property' => 'hc:ownedBy',
   'target' => 'hc:Person',
);
$relationship_assignments['businesses'][] = array(
   'property' => 'hc:locatedAt',
   'target' => array(
      'hc:BuildingOrPublicAmenity',
      'hc:CroftOrResidence',
      'hc:Location',
   ),
);
$relationship_assignments['businesses'][] = array(
   'property' => 'hc:employed',
   'target' => 'hc:Person',
);

/* Crofts and Residences */
$relationship_assignments['crofts_and_residences'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['crofts_and_residences'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
$relationship_assignments['crofts_and_residences'][] = array(
   'property' => 'hc:informationObtainedFrom',
   'target' => 'hc:Resource',
);
$relationship_assignments['crofts_and_residences'][] = array(
   'property' => 'hc:livedHere',
   'target' => 'hc:Person',
);
$relationship_assignments['crofts_and_residences'][] = array(
   'property' => 'hc:associatedWith',
   'target' => array(
      'hc:Boat',
      'hc:BuildingOrPublicAmenity',
      'hc:Business',
      'hc:CroftOrResidence',
      'hc:GaelicVerse',
      'hc:HistoricalEvent',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
      'hc:ObjectOrArtefact',
      'hc:Organisation',
      'hc:Person',
      'hc:StoryReportOrTradition',
      'hc:Vehicle',
   ),
);
$relationship_assignments['crofts_and_residences'][] = array(
   'property' => 'hc:locatedAt',
   'target' => 'hc:Location',
);
$relationship_assignments['crofts_and_residences'][] = array(
   'property' => 'hc:locatedHere',
   'target' => array(
      'hc:BuildingOrPublicAmenity',
      'hc:Business',
      'hc:LandmarkOrArchaeologicalSite',
   ),
);

/* Gaelic Verse */
$relationship_assignments['gaelic_verse'][] = array(
   'property' => 'hc:composedBy',
   'target' => 'hc:Person',
);
$relationship_assignments['gaelic_verse'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['gaelic_verse'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
$relationship_assignments['gaelic_verse'][] = array(
   'property' => 'hc:informationObtainedFrom',
   'target' => 'hc:Resource',
);
$relationship_assignments['gaelic_verse'][] = array(
   'property' => 'hc:associatedWith',
   'target' => array(
      'hc:Boat',
      'hc:BuildingOrPublicAmenity',
      'hc:Business',
      'hc:CroftOrResidence',
      'hc:GaelicVerse',
      'hc:HistoricalEvent',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
      'hc:ObjectOrArtefact',
      'hc:Organisation',
      'hc:Person',
      'hc:StoryReportOrTradition',
      'hc:Vehicle',
   ),
);

/* Historical Events */
$relationship_assignments['historical_events'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['historical_events'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
$relationship_assignments['historical_events'][] = array(
   'property' => 'hc:informationObtainedFrom',
   'target' => 'hc:Resource',
);
$relationship_assignments['historical_events'][] = array(
   'property' => 'hc:associatedWith',
   'target' => array(
      'hc:Boat',
      'hc:BuildingOrPublicAmenity',
      'hc:Business',
      'hc:CroftOrResidence',
      'hc:GaelicVerse',
      'hc:HistoricalEvent',
      'hc:HistoricalEvent',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
      'hc:ObjectOrArtefact',
      'hc:Organisation',
      'hc:Person',
      'hc:StoryReportOrTradition',
      'hc:Vehicle',
   ),
);

/* Historical/ Archaeological Sites */
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
   'property' => 'hc:isPartOfSite',
   'target' => 'hc:LandmarkOrArchaeologicalSite',
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
   'property' => 'hc:includesSubSite',
   'target' => 'hc:LandmarkOrArchaeologicalSite',
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
   'property' => 'hc:foundHere',
   'target' => 'hc:ObjectOrArtefact',
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
   'property' => 'hc:informationObtainedFrom',
   'target' => 'hc:Resource',
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
   'property' => 'hc:livedHere',
   'target' => 'hc:Person',
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
   'property' => 'hc:associatedWith',
   'target' => array(
      'hc:Boat',
      'hc:BuildingOrPublicAmenity',
      'hc:Business',
      'hc:CroftOrResidence',
      'hc:GaelicVerse',
      'hc:HistoricalEvent',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
      'hc:ObjectOrArtefact',
      'hc:Organisation',
      'hc:Person',
      'hc:StoryReportOrTradition',
      'hc:Vehicle',
   ),
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
   'property' => 'hc:locatedAt',
   'target' => array(
      'hc:CroftOrResidence',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
   ),
);

/* Locations */
$relationship_assignments['locations'][] = array(
   'property' => 'hc:bornHere',
   'target' => 'hc:Person',
);
$relationship_assignments['locations'][] = array(
   'property' => 'hc:diedHere',
   'target' => 'hc:Person',
);
$relationship_assignments['locations'][] = array(
   'property' => 'hc:immigratedHere',
   'target' => 'hc:Person',
);
$relationship_assignments['locations'][] = array(
   'property' => 'hc:emigratedFromHere',
   'target' => 'hc:Person',
);
$relationship_assignments['locations'][] = array(
   'property' => 'hc:movedFromHere',
   'target' => 'hc:Person',
);
$relationship_assignments['locations'][] = array(
   'property' => 'hc:movedToHere',
   'target' => 'hc:Person',
);
$relationship_assignments['locations'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['locations'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
$relationship_assignments['locations'][] = array(
   'property' => 'hc:foundHere',
   'target' => 'hc:ObjectOrArtefact',
);
$relationship_assignments['locations'][] = array(
   'property' => 'hc:informationObtainedFrom',
   'target' => 'hc:Resource',
);
$relationship_assignments['locations'][] = array(
   'property' => 'hc:livedHere',
   'target' => 'hc:Person',
);
$relationship_assignments['locations'][] = array(
   'property' => 'hc:locatedNear',
   'target' => array(
      'hc:NaturalLandscapeFeature',
      'hc:Location',
   ),
);
$relationship_assignments['locations'][] = array(
   'property' => 'hc:associatedWith',
   'target' => array(
      'hc:Boat',
      'hc:BuildingOrPublicAmenity',
      'hc:Business',
      'hc:CroftOrResidence',
      'hc:GaelicVerse',
      'hc:HistoricalEvent',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
      'hc:ObjectOrArtefact',
      'hc:Organisation',
      'hc:Person',
      'hc:StoryReportOrTradition',
      'hc:Vehicle',
   ),
);
$relationship_assignments['locations'][] = array(
   'property' => 'hc:locatedAt',
   'target' => 'hc:Location',
);
$relationship_assignments['locations'][] = array(
   'property' => 'hc:locatedHere',
   'target' => array(
      'hc:BuildingOrPublicAmenity',
      'hc:Business',
      'hc:CroftOrResidence',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
   ),
);

/* Natural Landscape Features */
$relationship_assignments['natural_landscape_features'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['natural_landscape_features'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
$relationship_assignments['natural_landscape_features'][] = array(
   'property' => 'hc:foundHere',
   'target' => 'hc:ObjectOrArtefact',
);
$relationship_assignments['natural_landscape_features'][] = array(
   'property' => 'hc:informationObtainedFrom',
   'target' => 'hc:Resource',
);
$relationship_assignments['natural_landscape_features'][] = array(
   'property' => 'hc:locatedNear',
   'target' => array(
      'hc:Location',
      'hc:NaturalLandscapeFeature',
   ),
);
$relationship_assignments['natural_landscape_features'][] = array(
   'property' => 'hc:associatedWith',
   'target' => array(
      'hc:Boat',
      'hc:BuildingOrPublicAmenity',
      'hc:Business',
      'hc:CroftOrResidence',
      'hc:GaelicVerse',
      'hc:HistoricalEvent',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:ObjectOrArtefact',
      'hc:Organisation',
      'hc:Person',
      'hc:StoryReportOrTradition',
      'hc:Location',
   ),
);
$relationship_assignments['natural_landscape_features'][] = array(
   'property' => 'hc:locatedAt',
   'target' => array(
      'hc:Location',
      'hc:NaturalLandscapeFeature',
   ),
);
$relationship_assignments['natural_landscape_features'][] = array(
   'property' => 'hc:locatedHere',
   'target' => array(
      'hc:LandmarkOrArchaeologicalSite',
      'hc:NaturalLandscapeFeature',
   ),
);

/* Objects and Artefacts */
$relationship_assignments['objects_and_artefacts'][] = array(
   'property' => 'hc:heldBy',
   'target' => 'hc:Organisation',
);
$relationship_assignments['objects_and_artefacts'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['objects_and_artefacts'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
$relationship_assignments['objects_and_artefacts'][] = array(
   'property' => 'hc:foundAt',
   'target' => array(
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
   ),
);
$relationship_assignments['objects_and_artefacts'][] = array(
   'property' => 'hc:informationObtainedFrom',
   'target' => 'hc:Resource',
);
$relationship_assignments['objects_and_artefacts'][] = array(
   'property' => 'hc:associatedWith',
   'target' => array(
      'hc:Boat',
      'hc:BuildingOrPublicAmenity',
      'hc:Business',
      'hc:CroftOrResidence',
      'hc:GaelicVerse',
      'hc:HistoricalEvent',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
      'hc:ObjectOrArtefact',
      'hc:Organisation',
      'hc:Person',
      'hc:Resource',
      'hc:StoryReportOrTradition',
      'hc:Vehicle',
   ),
);
$relationship_assignments['objects_and_artefacts'][] = array(
   'property' => 'hc:locatedAt',
   'target' => 'hc:BuildingOrPublicAmenity',
);

/* Organisations */
$relationship_assignments['organisations'][] = array(
   'property' => 'hc:compilerOf',
   'target' => 'hc:Resource',
);
$relationship_assignments['organisations'][] = array(
   'property' => 'hc:holds',
   'target' => array(
      'hc:ObjectOrArtefact',
      'hc:Resource',
   ),
);
$relationship_assignments['organisations'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['organisations'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
$relationship_assignments['organisations'][] = array(
   'property' => 'hc:informationObtainedFrom',
   'target' => 'hc:Resource',
);
$relationship_assignments['organisations'][] = array(
   'property' => 'hc:associatedWith',
   'target' => array(
      'hc:Boat',
      'hc:BuildingOrPublicAmenity',
      'hc:Business',
      'hc:CroftOrResidence',
      'hc:GaelicVerse',
      'hc:HistoricalEvent',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
      'hc:ObjectOrArtefact',
      'hc:Organisation',
      'hc:Person',
      'hc:StoryReportOrTradition',
      'hc:Vehicle',
   ),
);

/* People */
$relationship_assignments['people'][] = array(
   'property' => 'hc:livedAt',
   'target' => array(
      'hc:CroftOrResidence',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
   ),
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:married',
   'target' => 'hc:Person',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:siblingOf',
   'target' => 'hc:Person',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:parentOf',
   'target' => 'hc:Person',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:childOf',
   'target' => 'hc:Person',
);

$relationship_assignments['people'][] = array(
   'property' => 'hc:relatedTo',
   'target' => 'hc:Person',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:onCrewOfBoat',
   'target' => 'hc:Boat',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:movedFrom',
   'target' => 'hc:Location',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:movedTo',
   'target' => 'hc:Location',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:immigrantFrom',
   'target' => 'hc:Location',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:emigratedTo',
   'target' => 'hc:Location',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:livedWith',
   'target' => 'hc:Person',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:adopterOf',
   'target' => 'hc:Person',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:adoptedBy',
   'target' => 'hc:Person',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:fostererOf',
   'target' => 'hc:Person',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:fosteredBy',
   'target' => 'hc:Person',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:bornAt',
   'target' => 'hc:Location',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:diedAt',
   'target' => 'hc:Location',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:builderOfBoat',
   'target' => 'hc:Boat',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:authorCompilerOf',
   'target' => 'hc:Resource',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:mayBeTheSameAs',
   'target' => 'hc:Person',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:composedSong',
   'target' => 'hc:GaelicVerse',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:employedBy',
   'target' => array(
      'hc:Business',
      'hc:Person',
   ),
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:informationObtainedFrom',
   'target' => 'hc:Resource',
);

$relationship_assignments['people'][] = array(
   'property' => 'hc:associatedWith',
   'target' => array(
      'hc:Boat',
      'hc:BuildingOrPublicAmenity',
      'hc:Business',
      'hc:CroftOrResidence',
      'hc:GaelicVerse',
      'hc:HistoricalEvent',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
      'hc:ObjectOrArtefact',
      'hc:Organisation',
      'hc:Person',
      'hc:Person',
      'hc:Resource',
      'hc:StoryReportOrTradition',
      'hc:Vehicle',
   ),
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:owned',
   'target' => array(
      'hc:Boat',
      'hc:Business',
      'hc:Vehicle',
   ),
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:employed',
   'target' => 'hc:Person',
);
$relationship_assignments['people'][] = array(
   'property' => 'hc:sourceOf',
   'target' => 'hc:StoryReportOrTradition',
);

/* Resources */
$relationship_assignments['resources'][] = array(
   'property' => 'hc:compiledBy',
   'target' => 'hc:Organisation',
);
$relationship_assignments['resources'][] = array(
   'property' => 'hc:writtenCompiledBy',
   'target' => 'hc:Person',
);
$relationship_assignments['resources'][] = array(
   'property' => 'hc:heldBy',
   'target' => 'hc:Organisation',
);
$relationship_assignments['resources'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['resources'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
$relationship_assignments['resources'][] = array(
   'property' => 'hc:sourceOfInformationOn',
   'target' => array(
      'hc:Boat',
      'hc:BuildingOrPublicAmenity',
      'hc:Business',
      'hc:CroftOrResidence',
      'hc:GaelicVerse',
      'hc:HistoricalEvent',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
      'hc:ObjectOrArtefact',
      'hc:Organisation',
      'hc:Person',
      'hc:StoryReportOrTradition',
      'hc:Vehicle',
   ),
);
$relationship_assignments['resources'][] = array(
   'property' => 'hc:associatedWith',
   'target' => array(
      'hc:ObjectOrArtefact',
      'hc:Person',
      'hc:Resource',
   ),
);
$relationship_assignments['resources'][] = array(
   'property' => 'hc:locatedAt',
   'target' => 'hc:BuildingOrPublicAmenity',
);

/* Stories, Reports and Traditions */
$relationship_assignments['stories_reports_and_traditions'][] = array(
   'property' => 'hc:fromSource',
   'target' => 'hc:Person',
);
$relationship_assignments['stories_reports_and_traditions'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['stories_reports_and_traditions'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
$relationship_assignments['stories_reports_and_traditions'][] = array(
   'property' => 'hc:informationObtainedFrom',
   'target' => 'hc:Resource',
);
$relationship_assignments['stories_reports_and_traditions'][] = array(
   'property' => 'hc:associatedWith',
   'target' => array(
      'hc:Boat',
      'hc:BuildingOrPublicAmenity',
      'hc:Business',
      'hc:CroftOrResidence',
      'hc:GaelicVerse',
      'hc:HistoricalEvent',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:NaturalLandscapeFeature',
      'hc:ObjectOrArtefact',
      'hc:Organisation',
      'hc:Person',
      'hc:StoryReportOrTradition',
      'hc:StoryReportOrTradition',
      'hc:Vehicle',
   ),
);

/* Vehicles */
$relationship_assignments['vehicles'][] = array(
   'property' => 'hc:hasImageFile',
   'target' => 'hc:ImageFile',
);
$relationship_assignments['vehicles'][] = array(
   'property' => 'hc:hasSoundFile',
   'target' => 'hc:SoundFile',
);
$relationship_assignments['vehicles'][] = array(
   'property' => 'hc:informationObtainedFrom',
   'target' => 'hc:Resource',
);
$relationship_assignments['vehicles'][] = array(
   'property' => 'hc:associatedWith',
   'target' => array(
      'hc:Business',
      'hc:CroftOrResidence',
      'hc:GaelicVerse',
      'hc:HistoricalEvent',
      'hc:LandmarkOrArchaeologicalSite',
      'hc:Location',
      'hc:ObjectOrArtefact',
      'hc:Organisation',
      'hc:Person',
      'hc:StoryReportOrTradition',
      'hc:Vehicle',
   ),
);
$relationship_assignments['vehicles'][] = array(
   'property' => 'hc:ownedBy',
   'target' => array(
      'hc:Business',
      'hc:Person',
   ),
);

/* Image Details */

$relationship_assignments['image_details'][] = array(
   'property' => 'hc:isShownHere',
   'target' => $all_records,
);

/* Sound Files */

$relationship_assignments['sound_files'][] = array(
   'property' => 'hc:isHeardHere',
   'target' => $all_records,
);
