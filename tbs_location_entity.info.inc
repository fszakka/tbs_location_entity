<?php
class TbsLocationEntityMetadataController extends EntityDefaultMetadataController {
    public function entityPropertyInfo(){
        $info = parent::entityPropertyInfo();
        $properties = &$info[$this->type]['properties'];
        
        $properties['label'] = array(
            'label' => t('Label'),
            'description' => t('The location label.'),
            'setter callback' => 'entity_property_verbatim_set',
            'setter permission' => 'administer tbs location entites',
            'schema field' => 'label',
        );
        $properties['type'] = array(
            'type' => 'tbs_location_entity_type',
            'getter callback' => 'entity_property_getter_method',
            'setter callback' => 'entity_property_verbatim_set',
            'setter permission' => 'administer tbs location entites',
            'required' => TRUE,
            'description' => t('The Location entities type'),
        ) + $properties['type'];
        
        unset($properties['uid']);
        
        $properties['user'] = array(
            'label' => t("User"),
            'type' => 'user',
            'description' => t("The user who entered the location."),
            'getter callback' => 'entity_property_getter_method',
            'setter callback' => 'entity_property_setter_method',
            'setter permission' => 'administer tbs location entites',
            'required' => TRUE,
            'schema field' => 'uid',
        );
        
        $properties['created'] = array(
            'label' => t("Date Created"),
            'type' => 'date',
            'descrtiption' => t("The date the tbs Location entity was created."),
            'setter callback' => 'entity_property_verbatim_set',
            'setter permission' => 'administer tbs location entites',
            'schema field' => 'created',
        );
        
        $properties['changed'] = array(
            'label' => t("Date Changed"),
            'type' => 'date',
            'schema field' => 'changed',
            'description' => t("The date the location that was most recently updated."),
        );
        
        return $info;
    }
}