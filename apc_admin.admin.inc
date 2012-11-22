<?php
/**
 * APC Administration Interface
 */

/**
 * Main settings and review administration screen.
 */
function apc_admin_settings_form($form, &$form_state) {
  global $base_url;

  $form = array();

  if(!function_exists('apc_cache_info') || !(@apc_cache_info('opcode'))) {
    return array('#prefix' => t('No cache info available.  APC does not appear to be running.'));
  }

  drupal_add_css(drupal_get_path('module', 'apc_admin') . '/apc_admin.css');

  // Node author information for administrators.
  $form['apc_reset_cache'] = array(
    '#type' => 'fieldset',
    '#access' => user_access('administer nodes'),
    '#title' => t('Reset APC Cache'),
  );

  $form['apc_reset_cache']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Reset Cache'),
  );

  $form['apc_php'] = array(
    '#type' => 'fieldset',
    '#access' => user_access('administer nodes'),
    '#title' => t('APC Administration'),
  );

  $form['apc_php']['apc_php_iframe'] = array(
    '#markup' => '<iframe src="' . $base_url . '/' . drupal_get_path('module', 'apc_admin') . '/' . 'apc.php"></iframe>',
  );

  return $form;
}

/**
 * Handle cache reset
 */
function apc_admin_settings_form_submit($form, &$form_state) {
  apc_clear_cache();
  apc_clear_cache('user');
  apc_clear_cache('opcode');
  drupal_set_message(t('APC Cache cleared!'));
}
