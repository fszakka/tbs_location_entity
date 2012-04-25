<?php

/**
 * UI controller
 */
class TBSLocationEntityTypeUIController extends EntityDefaultUIController {
    /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage profiles, including fields.';
    return $items;
  }
}

/**
 * Generates the tbs Location type editing form
 */
function tbs_location_entity_type_form($form, &$form_state, $location_type, $op = 'edit') {
    if($op == 'clone') {
        $location_type->label .= ' (cloned)';
        $location_type->type = '';
    }
    
    $form['label'] = array(
        '#title' => t('Label'),
        '#type' => 'textfield',
        '#default_value' => $location_type->label,
        '#description' => t('The human-readable name of this location type.'),
        '#required' => TRUE,
        '#size' => 30,
    );
    $form['type'] = array(
        '#type' => 'machine_name',
        '#default_value' => isset($location_type->type) ? $location_type->type : '',
        '#maxlength' => 32,
        '#disabled' => $location_type->islocked() && $op !='clone',
        '#machine_name' => array(
            'exists' => 'tbs_location_entity_get_types',
            'source' => array('label'),
        ),
        '#description' => t('A unique machine-readable name'),
       );
    $form['data']['#tree'] = TRUE;
    $form['data']['islocal'] = array(
        '#type' => 'checkbox',
        '#title' => t('local location'),
        '#defauld_value' => !empty($location_type->data['islocal']),
    );
    
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save Location Type'),
        '#weight' => 40,
    );
    
    if($op != 'add' && $op != 'clone') {
        $form['actions']['delete'] = array(
            '#type' => 'submit',
            '#value' => t('Delete Location Type'),
            '#weight' => 45,
            '#limit_validation_errors' => array(),
            '#submit' => array('tbs_location_entity_type_form_submit_delete')
        );
    }
    return $form;
}
function tbs_location_entity_type_form_submit(&$form, &$form_state){
    $location_type = entity_ui_form_submit_build_entity($form, $form_state);
    $location_type->save();
    $form_state['redirect'] = 'admin/structure/locations';
}
function tbs_location_entity_type_form_submit_delete(&$form, &$form_state){
    $form_state['redirect'] = 'admin/structure/locations/manage/' . $form_state['tbs_location_entity_type']->type . '/delete';
}