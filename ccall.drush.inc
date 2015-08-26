<?php

/**
 * Implements hook_drush_cache_clear().
 */
function ccall_drush_cache_clear(&$types) {
  $types['all'] = '__ccall_clear_really_everything';
}

/**
 * Helper function to clear all caches. Really all of them.
 */
function __ccall_clear_really_everything() {
  $types = drush_cache_clear_types(drush_has_boostrapped(DRUSH_BOOTSTRAP_DRUPAL_FULL));

  // Again, we are only aiming to clear Drupal caches.
  unset($types['drush']);

  // The following are taken care of in drupal_flush_all_caches()
  // and functions called therein.
  unset($types['theme-registry']);
  unset($types['menu']);
  unset($types['css-js']);
  unset($types['module-list']);
  unset($types['theme-list']);
  unset($types['registry']);

  // Don't want to incur in an infinite recursion.
  unset($types['all']);

  // Clear 'all' caches.
  if (drush_has_boostrapped(DRUSH_BOOTSTRAP_DRUPAL_FULL)) {
    drupal_flush_all_caches();
  }

  // Clear the remaining caches.
  foreach ($types as $type => $callback) {
    drupal_set_message("Clearing cache: $type");
    if (function_exists($callback)) {
      call_user_func($callback);
    }
  }
}
