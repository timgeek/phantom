<?php

/**
 * @file
 * Features module drush integration.
 */

/**
 * Implements hook_drush_command().
 *
 * @return
 *   An associative array describing your command(s).
 *
 * @see drush_parse_command()
 */
function phantom_drush_command() {
  $items = array();

  $items['phantom-render'] = array(
    'description' => "Render a Drupal path.",
    'options' => array(
      'path' => "Drupal path to be rendered [required]",
      'mode' => "Output mode: jpg, png or pdf [defaults to pdf]",
      'height' => "Height in pixels.  [defaults to 720]",
      'width' => "Width in pixels.  [defaults to 1280]",
    ),
    'drupal dependencies' => array('phantom'),
    'aliases' => array('phr'),
  );
  $items['phantom-test'] = array(
    'description' => "Test for DOM elements in Drupal path.",
    'options' => array(
      'path' => "Drupal path to be rendered [required]",
      'test' => "DOM element from which to extract text [required]",
      'type' => "DOM element type.  [defaults to null]",
    ),
    'drupal dependencies' => array('phantom'),
    'aliases' => array('pht', 'phat'),
  );
  $items['phantom-speed'] = array(
    'description' => "Test for DOM elements in Drupal path.",
    'options' => array(
      'path' => "Drupal path to be rendered [required]",
    ),
    'drupal dependencies' => array('phantom'),
    'aliases' => array('phast'),
  );

  return $items;
}

function drush_phantom_render() {
  if (!drush_get_option('path')) {
    return drush_set_error('', 'Path is a required option.');
  }
  else {
    foreach (array('path', 'mode', 'height', 'width') AS $option) {
      $$option = drush_get_option($option);
    }
    module_load_include('module', 'phantom', 'phantom');
    $output = phantom_phantom($path, $mode, $height, $width, TRUE);
    drush_print(print_r($output, 1));
  }
}

function drush_phantom_test() {
  if (!drush_get_option('path')) {
    return drush_set_error('', 'Path is a required option.');
  }
  else {
    foreach (array('path', 'test', 'type') AS $option) {
      $$option = drush_get_option($option);
    }
    module_load_include('module', 'phantom', 'phantom');
    $output = phantom_test($path, $test, $type, TRUE);
    //drush_print(print_r($output,1));
    $rows = array();
    unset($output[0]);
    unset($output[1]);
    foreach ($output AS $row) {
      $trimmd_row = array();
      foreach (explode(': ', $row) AS $cell) {
        $trimmed_row[] = trim($cell);
      }
      $rows[] = $trimmed_row;
    }
    drush_print_table($rows, TRUE);
  }
}

function drush_phantom_speed() {
  if (!drush_get_option('path')) {
    return drush_set_error('', 'Path is a required option.');
  }
  else {
    $path = drush_get_option('path');
    module_load_include('module', 'phantom', 'phantom');
    $output = phantom_speed($path, TRUE);
    drush_print(print_r($output, 1));
  }
}

