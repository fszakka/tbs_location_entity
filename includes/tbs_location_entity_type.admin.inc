<?php
/**
 * Page to select a location
 */
function tbs_location_entity_admin_add_page() {
    $items = array();
    foreach(tbs_location_entity_get_types() as $type => $info) {
            $items[] = l(entity_label('tbs_location_entity_type', $info), 'tbslocation/add/' . $type);
    }
    
    
    return array('list' => array('#theme' => 'item_list', '#items' => $items, '#title' => t('Select a type of Location to create')));
}

/**
 * Add a new location attribute
 */
function tbs_location_entity_add($type) {
    
    $location_type = tbs_location_entity_get_types($type);
    
    $location_entity = entity_create('tbs_location_entity', array('type' => $type));
    drupal_set_title(t('Add locations that are related to [ @name ]', array('@name' => entity_label('tbs_location_entity_type', $location_type))));
    
    $output = drupal_get_form('tbs_location_entity_attribute_form', $location_entity);
      
    return $output;
}
/**
 * tbs location entities form
 */
function tbs_location_entity_attribute_form($form, &$form_state, $location_type){
    $form_state['location'] = $location_type;
    
    global $user;
    
    $form['label'] = array(
        '#type' => 'textfield',
        '#required' => TRUE,
        '#title' => t('Name'),
        '#default_value' => '',
        '#description' => t('Add location names that are related to @name ', array('@name' => $location_type->label)),
    );
    
    $form['uid'] = array(
        '#type' => 'value',
        '#value' => $user->uid,
    );
    
    $form['created'] = array(
        '#type' => 'value',
        '#value' => REQUEST_TIME,
    );
    
    field_attach_form('tbs_location_entity', $location_type, $form, $form_state);
    
    $submit = array();
    
    if(!empty($form['#submit'])) {
        $submit += $form['#submit'];
    }
    
    $form['actions'] = array(
        '#weight' => 100,
    );
    
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save location attributes'),
        '#submit' => $submit + array('tbs_location_entity_entity_form_submit'),
    );
    
    $location_type_id = entity_id('tbs_location_entity', $location_type);
    if(!empty($location_type_id) && tbs_location_entity_access('edit', $location_type)) {
        $form['actions']['delete'] = array(
            '#type' => 'submit',
            '#value' => t('Delete'),
            '#submit' => array('tbs_location_entity_entity_form_submit_delete'),
        );
    }
    
    $form['#validate'][] = 'tbs_location_entity_entity_form_validate';
    
    return $form;
}

function tbs_location_entity_entity_form_validate($form, &$form_state) {
    
}

/**
 * Tbs Location Entity Submit Handler
 */
function tbs_location_entity_entity_form_submit($form, &$form_state){
    $location_type = $form_state['location'];
    
    entity_form_submit_build_entity('tbs_location_entity',$location_type,$form,$form_state);
    
    entity_save('tbs_location_entity', $location_type);
   
   $location_uri = entity_uri('tbs_location_entity', $location_type);
   
   $form_state['redirect'] = $location_uri['path'];
   
   drupal_set_message(t('Location %title Saved.', array('%title'=> entity_label('tbs_location_entity',$location_type))));
    
}

function tbs_location_entity_entity_form_submit_delete($form, &$form_state){
     $location_type = $form_state['location'];
     $location_uri = entity_uri('tbs_location_entity', $location_type);
     $form_state['redirect'] = $location_uri['path'] . '/delete';
}

/**
 * Delete Confirmation form
 */
function tbs_location_entity_entity_delete_form($form, &$form_state, $location_type){
    $form_state['location'] = $location_type;
    $form['location_entity_id'] = array('#type' => 'value',
                                        '#value' => entity_id('tbs_location_entity', $location_type));
    $location_entity_uri = entity_uri('tbs_locaion_entity', $location_type);
     return confirm_form($form,
    t('Are you sure you want to delete the location %title?', array('%title' => entity_label('tbs_locaion_entity', $location_type))),
    $location_entity_uri['path'],
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Delete form submit handler.
 */
function tbs_location_entity_entity_delete_form_submit($form, &$form_state){
    $location_type = $form_state['location'];
    entity_get_controller('tbs_location_entity')->delete($location_type);
    drupal_set_message(t('locatuib %title deleted.', array('%title' => entity_label('tbs_location_entity', $location_type))));

  $form_state['redirect'] = '<front>';
}