<?php

/**
 * tbs location entity callback View
 */
function tbs_location_entity_view($location) {
    drupal_set_title(entity_label('tbs_location_entity', $location));
    return entity_view('tbs_locaton_entity', array(entity_id('tbs_location_entity', $location) => $location), 'full');
}