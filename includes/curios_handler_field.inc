<?php
/*
 * curios_handler_field.inc
 * 
 * Copyright (c) 2011-2013, Hai Nguyen  (hai.nguyen@abdn.ac.uk) Stuart Taylor (staylor@abdn.ac.uk),
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
 * Field handler to rewrite link targets generated in curios.views.inc.
 */
class curios_link_target_rewriter extends views_handler_field {

  /**
   * Implements views_handler_field#query().
   */
  function query() {
    $this->field_alias = 'curios_rewrite_link_' . $this->position;
  }

  /**
   * Implements views_handler_field#render().
   */
  function render($values) {
    // Replace the link target path.
    $config = curios_configuration();
    $display = $this->view->display[$this->view->current_display];
    $targets = $display->display_options['curios']['relationship_targets'];
    $id_field = $config->getDefaultResourceId() .'_'. $config->getIdentifierFieldId();
    $subject_id = $values->$id_field;
    $target_view = $config->getViewSpec($targets[$subject_id]);
    $target_path = $target_view->getPath();
    $this->options['alter']['path'] =  $target_path. strstr($this->options['alter']['path'], '/');
  
    return parent::render($values);
  }
}

/**
 * Field handler to output HTML that displays thumbnail images using Timthumb and Lightbox.
 */
class curios_image_thumbnail_field extends views_handler_field {

  function query() {
    $this->field_alias = 'curios_image_thumb_' . $this->position;
  }

  function render($values) {

    $config = curios_configuration();
    $image_url_field = $config->getImageResourceId() .'_'. $config->getURLFieldId();
    $image_url = $values->$image_url_field;
    global $base_url;
    $image_url = str_replace('http://www.hebrideanconnections.com/', $base_url.'/', str_replace(' ','%20',$image_url));

    $moreinfo_link = '';
    if (isset($this->options['view_path']) && isset($this->options['view_path']))
    	$moreinfo_link =  ' <a href=\''.$GLOBALS['base_path'] .$this->options['view_path'].'/'.$values->{$this->options['id_field']}.'\'>('.t('more info').')</a>';
    $title = $values->{$this->options['title_field']} .$moreinfo_link ;
    $title = str_replace('"', '\'', $title);
    if (isset($this->options['disable_thumbnail']) && $this->options['disable_thumbnail'] = TRUE) { // Display full size image.
      $image_output = "<a href=\"$image_url\" title=\"$title\" rel=\"lightbox[gallery]\"><img src=\"$image_url\" alt=\"$title\" /></a>";
    } else { // Generate thumbnail.
      $thumbnail = theme('imagecache_external', array('path' => $image_url, 'style_name'=> 'medium','alt'=>$title));
      $image_output = "<a href=\"$image_url\" title=\"$title\" rel=\"lightbox[gallery]\">$thumbnail</a>";
    }

    return $image_output;
  }
}

class curios_sound_handler_field extends views_handler_field {

  function query() {
    $this->field_alias = 'curios_sound_file';
  }

  function render($values) {

    $config = curios_configuration();
    $sound_url_field = 'hc_sound_file_'. $config->getURLFieldId();
    $sound_url = $values->$sound_url_field;
    global $base_url;
    $sound_url = str_replace('http://www.hebrideanconnections.com/', $base_url.'/', str_replace(' ','%20',$sound_url));

    $title = addslashes($values->{$this->options['title_field']}) ;
    
    $sound_output = "<audio id='audio_player_single' src='$sound_url' title='$title' > </audio>";
    return $sound_output;
  }
}


class curios_date_range_field extends views_handler_field {

  function query() {
    $this->field_alias = 'curios_date_range_' . $this->position;
  }

  function render($values) {
    $result_position = $this->options['date_range_position'];
    $field_suffix = ($result_position > 0) ? '_'.$result_position : '';

    $date_range_from_field = $this->options['date_range_from'] . $field_suffix;
    $date_range_to_field = $this->options['date_range_to'] . $field_suffix;

    if (isset($values->{$date_range_from_field})) {
      $dateFrom = $values->{$date_range_from_field};
      $dateTo = $values->{$date_range_to_field};

      return curios_format_daterange($dateFrom, $dateTo);
    } else {
      return '';
    }
  }
}
