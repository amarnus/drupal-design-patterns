<?php

// http://harrypotter.wikia.com/wiki/Marauder's_Map
function design_patterns_observer_notify_form($form, &$form_state) {
  $form['message'] = array(
    '#type' => 'markup',
    '#markup' => t('Imagine you are Severus Snape. Go on, open the Marauder\'s map.')
  );
  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['notify'] = array(
    '#type' => 'submit',
    '#value' => t('Open the Marauder\'s map'),
    '#submit' => array('design_patterns_observer_notify_form_submit')
  );
  $form['actions']['refresh'] = array(
    '#type' => 'submit',
    '#value' => t('Close the map'),
    '#submit' => array('design_patterns_observer_notify_form_refresh')
  );
	return $form;
}

function design_patterns_observer_notify_form_submit($form, &$form_state) {
  // Snape has opened the map..
  module_invoke_all('design_patterns_observer_notify', 'open_map');
}

function design_patterns_observer_notify_form_refresh($form, &$form_state) {
  // Snape has closed the map..
  module_invoke_all('design_patterns_observer_notify', 'close_map');
  $form_state['redirect'] = current_path();
}