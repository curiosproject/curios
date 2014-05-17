/*
 * curios-date-handler.js
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
    Drupal.behaviors.field_date = {
        attach: function(context, settings) {
	    $(".datetime-type").live("focus", function(event) {
                //$(this).attr('disabled', true);
                $(this).blur();
                $(this).next().children(".update-date-btn").trigger("click"); // TODO onclick form field to trigger date widget.
		
            //    alert("Please click Edit Date to input a new date.");
            });
            $(".update-date-btn").live("click", function(event) {
  		$(".date-input-widget").hide();                              
		var this_widget = $(this).next("div");
                var this_current_date_field = $(this).parent().prev(".datetime-type");
                //this_widget.load(Drupal.settings.curios.path + "/js/ldcms-daterange-form.html");
                $(this_widget).html('<span class="exact-date-widget">   '
+'    Date: <input name="exact-date-text" type="date">&nbsp;&nbsp;'
+'</span>'
+''
+'Exact <input checked="checked" name="circa" value="false" type="radio">'
+'Circa <input name="circa" value="true" type="radio"> <br>'
+'<div class="circa-date-widget" style="display:none;" > '
+'    <input name="circa-type" value="1" type="radio" style="float:left;width:10%;"/>'
+'    <span  class="input_1"> Season: '
+'        <select  name="season">'
+'            <option selected="selected" value="Spring">Spring</option>'
+'            <option value="Summer">Summer</option>'
+'            <option value="Autumn">Autumn</option>'
+'            <option value="Winter">Winter</option>'
+'        </select> '
+'        Year: <input placeholder="Enter a 4-digit year, e.g., 1990" style="width:40%;" class="date-input-text form-text" maxlength="4" size="4" name="season_year"  disabled type="text"/>'
+'    </span>'
+'    <div style="clear:both;"/>'
+'    <input name="circa-type" value="2" type="radio" style="float:left;width:10%;"/>'
+'    <span  class="input_2"> Year: <input placeholder="Enter a 4-digit year format for a year, e.g., 2000" style="float:right;width:70%;" disabled class="date-input-text form-text" maxlength="4" size="4" name="year" type="text"/><br>'
+'    </span>'
+'    <div style="clear:both;"/>'
+'    <input name="circa-type" value="3" type="radio" style="float:left;width:10%;">Decade: </input>'
+'    <span  class="input_3"> <input placeholder="Enter a 4-digit year format for a decade, e.g., 2000, 1990 etc" style="float:right;width:70%;" disabled class="date-input-text form-text" maxlength="5" size="5" name="decade" type="text"><br>'
+'    </span>'
+'    <div style="clear:both;"/>'
+'    <input name="circa-type" value="4" type="radio" style="float:left;width:10%;"> Century:</input>'
+'    <span  class="input_4"> <input  placeholder="Enter a 2-digit century format with optional th/st/nd/rd, e.g., 20th, 19, 21st etc" style="float:right;width:70%;" disabled class="date-input-text form-text" maxlength="4" size="4" name="century" type="text"><br>'
+'    </span>'
+'    <div style="clear:both;"/>'
+'    <input name="circa-type" value="5" type="radio" style="float:left;width:10%;"/>'
+'    <span  class="input_5"> Start date: <input class="form-text" disabled name="start_date" type="date">'
+'        End date: <input name="end_date" class="form-text" disabled type="date"><br>'
+'    </span>'
+'    <div style="clear:both;"/>'
+''
+'</div>'
+'<div>'
+'    <div class="date-input-msg"></div>'
+'    <input class="confirm-date" value="Confirm New Date" type="button">'
+'    <input class="delete-date" value="Delete Current Date" type="button">'
+'</div>');
	
		// add date picker to all date field (fix bugs for uninitialised datepickers in other browers than Chrome.) 26/02/14 -- hhn
		$("[type=date]").datepicker({ dateFormat: 'yy-mm-dd' });

                $(this_widget).show();
                this_current_date_field.attr('disabled', true);
                $(".update-date-btn").show();
                $(this).hide();

            });


            // switching between widgets
            $('input[name=circa]').live('click', function(event) {
                var is_circa = $(this).val();
                if (is_circa == "true")
                {
                    $(this).prevAll(".exact-date-widget").hide();
                    $(this).nextAll(".circa-date-widget").show();
                }
                else
                {  
                    $(this).prevAll(".exact-date-widget").show();
                    $(this).nextAll(".circa-date-widget").hide();
                }
                $("div.date-input-msg").html("");
            });

            // handler for radios
            $('input[name=circa-type]').live('click', function(event) {
                var index = $(this).val();
                // reset other text fields
                $('.date-input-text').attr('disabled', true);
                $('.date-input-text').val("");
                $(this).nextAll('.input_' + index).children('input').removeAttr('disabled');
            });
	    // handle delete date. a date range is delete by setting new values to empty string
            $('.delete-date').live('click', function(event) {
	    	var closestDateWidget = $(this).closest("div.form-item");
                var startDateInput = closestDateWidget.next("input[name|='startdate']");
                var endDateInput = closestDateWidget.next().next("input[name|='enddate']");
                var msg = $(this).prevAll("div.date-input-msg");
		msg.css('color', 'green');
                msg.html("You have delete the current date range successfully!<br/>");
		closestDateWidget.children('.datetime-type').val("");
                startDateInput.val("");
                endDateInput.val("");
            });
            // handler for confirm button
            /*
             * Depending on the chosen input form, a validating function is called
             * and the result is retrieved in form of an array of 2 elements
             *  (startdate,enddate). Appropriate msg is also presented to users
             *  Red message means there is an error on the input
             *  Green message means that it is successful
             */
            $('.confirm-date').live('click', function(event) {
                var closestDateWidget = $(this).closest("div.form-item");
                var startDateInput = closestDateWidget.next("input[name|='startdate']");
                var endDateInput = closestDateWidget.next().next("input[name|='enddate']");

                // declare msg area and reset text
                var msg = $(this).prev("div.date-input-msg");
                msg.html("");
                var result, validated = false;

                // if exact date is chosen
                var is_circa = $(this).parent().prevAll('input[name=circa]:checked').val();
                if (is_circa == "false")
                {
		    var exactDate = $(this).parent().prevAll("span.exact-date-widget").children("input").val().trim();
                    validated = validate_date(exactDate, msg);
                    if (validated)
                        result = new Array(exactDate + 'T00:00:00'
                                , exactDate + 'T24:00:00');
                }
                else
                        // else using circa type
                        {

                            var chosen = $('input[name=circa-type]:checked');
                            switch (chosen.val())
                            {
                                case "1":
                                    var strYear = chosen.next().children('input[name=season_year]').val().trim();
                                    validated = validate_year(strYear, msg);
                                    if (validated)
                                        result = season_to_date($('select[name=season]').val(), parseInt(strYear));
                                    break;
                                case "2":
                                    var strYear = chosen.next().children('input[name=year]').val().trim();
                                    validated = validate_year(strYear, msg);
                                    if (validated)
                                        result = new Array(strYear + '-01-01' + 'T00:00:00'
                                                , strYear + '-12-31' + 'T24:00:00');
                                    break;
                                case "3":
                                    var strDecade = chosen.next().children('input[name=decade]').val().trim();
                                    validated = validate_decade(strDecade, msg);
                                    if (validated)
                                        result = decade_to_date(strDecade);
                                    break;
                                case "4":
                                    var strCentury = chosen.next().children('input[name=century]').val().trim();
                                    validated = validate_century(strCentury, msg);
                                    if (validated)
                                        result = century_to_date(strCentury);
                                    break;
                                case "5":
                                    var strStartDate = chosen.next().children('input[name=start_date]').val().trim();
                                    var strEndDate = chosen.next().children('input[name=end_date]').val().trim();

                                    validated = validate_daterange(strStartDate, strEndDate, msg);
                                    if (validated)
                                        result = new Array(strStartDate + 'T00:00:00'
                                                , strEndDate + 'T24:00:00');
                                    break;
                                default:
                                    validated = false;
                                    msg.css('color', 'red');
                                    msg.html("Please choose to enter a date-range");

                            }
                        }
                if (validated)
                {
                    msg.css('color', 'green');
                    msg.html("You have entered a new date range successfully!<br/>\n\
                      Start-date: " + result[0] + "<br/>\n\
                      End-date: " + result[1]);
                    startDateInput.val(result[0]);
                    endDateInput.val(result[1]);
		   $(this).attr('disabled', true);
                }
            });
        }
    }


})(jQuery);

function season_to_date(season, year) {

    var next_year = year + 1;
    switch (season.toLowerCase()) {
        case "winter":
            start_date = year + '-12-01' + 'T00:00:00';
            end_date = next_year + '-02-28' + 'T24:00:00';
            break;
        case "autumn":
            start_date = year + '-09-01' + 'T00:00:00';
            end_date = year + '-11-30' + 'T24:00:00';
            break;
        case "summer":
            start_date = year + '-06-01' + 'T00:00:00';
            end_date = year + '-08-31' + 'T24:00:00';
            break;
        case "spring":
            start_date = year + '-03-01' + 'T00:00:00';
            end_date = year + '-05-31' + 'T24:00:00';
            break;
    }

    return new Array(start_date, end_date);
}

function decade_to_date(decade) {
    var decadeStr = decade.substr(0, 3);
    start_date = decadeStr + '0-01-01' + 'T00:00:00';
    end_date = decadeStr + '9-12-31' + 'T24:00:00';
    return new Array(start_date, end_date);
}
function century_to_date(century) {
    var centuryStr = century.substr(0, 2);
    var centuryInt = parseInt(centuryStr) - 1;
    if (centuryInt<10)
    {
        start_date = '0'+centuryInt + '00-01-01' + 'T00:00:00';
        end_date = '0'+centuryInt + '99-12-31' + 'T24:00:00';
    }
    else 
    {
        start_date = centuryInt + '00-01-01' + 'T00:00:00';
        end_date = centuryInt + '99-12-31' + 'T24:00:00';
        
    }
        return new Array(start_date, end_date);
}
function validate_date(strDate, msg) {
    if (strDate == "")
    {
        msg.css('color', 'red');
        msg.html("Date missing. Please choose the date from the date-picker. If you don't have an exact date, try circa input.");
        return false;
    }
    return true;
}

function validate_daterange(strStartDate, strEndDate, msg) {
    if (strStartDate == "")
    {
        msg.css('color', 'red');
        msg.html("Start Date missing. Please choose both start-date and end-date from the date-picker.");
        return false;
    }
    if (strEndDate == "")
    {
        msg.css('color', 'red');
        msg.html("End Date missing. Please choose both start-date and end-date from the date-picker.");
        return false;
    }
    var startDate = new Date(strStartDate);
    var endDate = new Date(strEndDate);
    if (startDate > endDate)
    {
        msg.css('color', 'red');
        msg.html("Start-date (" + startDate.toDateString() + ") is before end-date (" + endDate.toDateString() + ").");
        return false;
    }

    return true;
}

function validate_century(century, msg) {

    var centuryPattern = /^[0-2]?[0-9]{1}(st|th|nd|rd)?$/;
    if (!centuryPattern.test(century))
    {
        msg.css('color', 'red');
        msg.html("Invalid century format: " + century + ". Please re-enter decade in 2-digit numeric format (e.g., 17 or 18th).");
        return false;
    }
    return true;
}

function validate_decade(decade, msg) {

    var decadePattern = /^[0-9]{1}[0-9]{2}[0-9]{1}[s]?$/;
    if (!decadePattern.test(decade))
    {
        msg.css('color', 'red');
        msg.html("Invalid decade format: " + decade + ". Please re-enter decade in 4-digit numeric format (e.g., 1990s).");
        return false;
    }
    return true;
}

function validate_year(year, msg) {
    var yearPattern = /^[0-9]{1}[0-9]{3}$/; // from 0000 to 9999 :)

    if (!yearPattern.test(year))
    {
        msg.css('color', 'red');
        msg.html("Invalid year format: " + year + ". Please re-enter year in 4-digit numeric format.");
        return false;
    }
    return true;
}
