/*
 * curios-map-view-handler.js
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
    Drupal.behaviors.mapview_single = {
        attach: function(context, settings) {
	// set name for coordinate fields (for example geo:lat, hc:northing...). Check the configuration file under options/map_settings
	  var 	x = settings.curiosMap.mapXName, 
    	      	y = settings.curiosMap.mapYName,
	      	defaultZoom = settings.curiosMap.defaultZoom;	
		x=x.replace('_','-');
		
		var X = $("div[class$="+x+"] span:last-child").html();
		if(!!X)
		{	y=y.replace('_','-');			
			var Y = $("div[class$="+y+"] span:last-child").html();
			$("div[class$=curios-summary-row]").after("<div id=osmap></div>")
			$('#osmap').css("width", "100%");
			$('#osmap').css("height", "400px"); 
			var marker = new OpenSpace.MapPoint(X,Y);
			osMap = new OpenSpace.Map("osmap");
			osMap.setCenter(marker, defaultZoom);
			osMap.createMarker(marker);
		}
           
        }
    }


})(jQuery);




