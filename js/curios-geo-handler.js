/*
 * curios-geo-handler.js
 * 
 * Copyright (c) 2011-2014, University of Aberdeen, Hai Nguyen (hai.nguyen@abdn.ac.uk). All rights reserved.
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
var osMap, dragControl, marker, mapMarker;
(function($) {
    Drupal.behaviors.field_geo = {
        attach: function(context, settings) {
	// set name for coordinate fields (for example geo:lat, hc:northing...). Check the configuration file under options/map_settings
	  var 	x = settings.curiosMap.mapXName, 
    	      	y = settings.curiosMap.mapYName,
	      	defaultZoom = settings.curiosMap.defaultZoom,
		defaultN = settings.curiosMap.defaultN,
		defaultE = settings.curiosMap.defaultE;
            // switching between widgets
            $('input[name='+y+'],input[name='+x+']').live("focus", function(event) {
		// if already loaded, don't reload;
		if ($('#map').attr("loaded")) return;
		$('#map').attr("loaded",true);
		$('#map').css("width", "100%");
		$('#map').css("height", "500px"); 
		var E = $("input[name=old_"+x+"]").val(), N = $("input[name=old_"+y+"]").val();
		if ((E=="")||isNaN(E)) E = defaultE;
		if ((N=="")||isNaN(N)) N = defaultN;
		var initialCenterPoint = new OpenSpace.MapPoint(E,N);
		createMap(initialCenterPoint);
                osMap.createMarker(initialCenterPoint);
		createDragControl();
                osMap.addControl(dragControl);
                activateDragControl();
		if (E!=defaultE || N!=defaultN) 
			updateMarkerPositionToTextfield(initialCenterPoint);
            });
            $('input[name='+y+'],input[name='+x+']').live("blur", function(event) {
		// update the marker based on textfield values
		var E = $("input[name="+x+"]").val(), N = $("input[name="+y+"]").val();
		if ((E=="")||isNaN(E)) E = defaultE;
		if ((N=="")||isNaN(N)) N = defaultN;
		var newCenterPoint = new OpenSpace.MapPoint(E,N);
		osMap.getMarkerLayer().clearMarkers();
		osMap.createMarker(newCenterPoint);
		osMap.setCenter(newCenterPoint);
	   });

        // creates the hand map centred on the initialCenterPoint

	function createMap(initialCenterPoint) {
	  
		osMap = new OpenSpace.Map("map");
		osMap.setCenter(initialCenterPoint, defaultZoom);
	}


	// updates the display text to the marker location

	function updateMarkerPositionToTextfield(lonlat) {
	  
		document.getElementsByName(x)[0].value = Math.round(lonlat.lon);
		document.getElementsByName(y)[0].value = Math.round(lonlat.lat);
	}

	// creates the drag control for the map

	function createDragControl() {
	  

	// Set dragging active on the default maker layer on map

		dragControl = new OpenSpace.Control.DragMarkers(osMap.getMarkerLayer(),{

	// onDrag create a lonlat variable with the lonlat (easting/northing in this projection) of the marker

			onDrag: function( marker ){
				var lonlat = marker.lonlat;
				updateMarkerPositionToTextfield(lonlat);
			},

	// onComplete centre boths maps on the marker lonlat

			onComplete: function( marker ){
				var lonlat = marker.lonlat;
		                osMap.setCenter(lonlat);
			}
		});
	}

	// Create the marker on the left hand map with the initial centre point


	// Centre both maps on the lonlat passed through


	function updateMapMarkerPosition(lonlat){
		osMap.getMarkerLayer().clearMarkers();
		mapMarker = osMap.createMarker(lonlat);
		osMap.setCenter(lonlat);
	}
	// Activate the dragcontrol

	function activateDragControl() {
		dragControl.activate();  
		osMap.getMarkerLayer().setDragMode(true);
	}
        
            
        }
    }


})(jQuery);




