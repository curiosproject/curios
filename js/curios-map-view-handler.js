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
(function($) {
    Drupal.behaviors.mapview_single = {
        attach: function(context, settings) {
            // set name for coordinate fields (for example geo:lat, hc:northing...). Check the configuration file under options/map_settings
            var x = settings.curiosMap.mapXName,
                y = settings.curiosMap.mapYName,
                defaultZoom = settings.curiosMap.defaultZoom;
            x = x.replace('_', '-');


            if (x.toLowerCase().indexOf('east') + x.toLowerCase().indexOf('north') >= 0) {
                var X = $("div[class$=" + x + "] span:last-child").html();
                if (!!X) {
                    y = y.replace('_', '-');
                    var Y = $("div[class$=" + y + "] span:last-child").html();
                    $("div[class$=curios-summary-row]").after("<div id=osmap></div>");
                    var marker = new OpenSpace.MapPoint(X, Y);
                    var osMap = new OpenSpace.Map("osmap");
                    osMap.setCenter(marker, defaultZoom);
                    osMap.createMarker(marker);
                }




                // This function creates the map 

                $(document).ready(function() {



                    var pos;
                    var places = $(".curios-place").map(function() {
                        return this.innerHTML;
                    }).get();
                    if (places.length > 0) {
                        // Create new map
                        $(".view-map-view").after("<div id=multimap></div>");
                        var multimap = new OpenSpace.Map('multimap');

                        for (var i = 0; i < places.length; i++)

                        {
                            var columns = places[i].split(',');
                            if (columns.length == 4) {
                                var x = parseFloat(columns[1]);
                                var y = parseFloat(columns[2]);
                                pos = new OpenSpace.MapPoint(x, y);
                                var popupText = '<a href="subjects/' + columns[0] + '">' + columns[3] + '</a>';
                                multimap.createMarker(pos, null, popupText);

                            } //endif
                        } //end for
                        multimap.setCenter(pos, defaultZoom);
                        // marker clustering
                        var clusterControl = new OpenSpace.Control.ClusterManager();
                        multimap.addControl(clusterControl);
                        clusterControl.activate();
                    }


                });


            }
            else // Leaflet maps
            {
                
                var X = $("div[class$=" + x + "] span:last-child").html();
                if (!!X) // if there exists coordinates
                {
                    y = y.replace('_', '-');
                    var Y = $("div[class$=" + y + "] span:last-child").html();
                    $("div[class$=curios-summary-row]").after("<div id='llmap'></div>");

                // var llmap = L.map('llmap').setView([X, Y], defaultZoom);
                //     L.tileLayer('http://{s}.tiles.mapbox.com/v3/{id}/{z}/{x}/{y}.png', {
                //         attribution: 'Imagery &copy; <a href="http://mapbox.com">Mapbox</a>'
                //         ,id:    'examples.map-i875mjb7'             
                //     }).addTo(llmap);
                } 
                
            }
        }
    }


})(jQuery);