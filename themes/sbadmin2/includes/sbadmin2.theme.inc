<?php

// Preprocess Theme.

/**
 * Implements hook_preprocess_HOOK(). Preprocess theme `node_form`.
 */
function sbadmin2_preprocess_node_form(&$variables) {
    hide($variables['form']['actions']);
    hide($variables['form']['additional_settings']);
}

// Preprocess Theme Wrapper.

/**
 * Implements template_preprocess_HOOK().
 *
 * @see template_preprocess()
 * @see template_process()
 */
function sbadmin2_preprocess_input_group(&$variables) {
    sbadmin2_utils::preprocess_theme_wrapper($variables, 'input-group');
}

/**
 * Implements template_preprocess_HOOK().
 *
 * @see template_preprocess()
 * @see template_process()
 */
function sbadmin2_preprocess_input_group_button(&$variables) {
    sbadmin2_utils::preprocess_theme_wrapper($variables, 'input-group-btn');
}

/**
 * Implements template_preprocess_HOOK().
 *
 * @see template_preprocess()
 * @see template_process()
 */
function sbadmin2_preprocess_input_group_addon(&$variables) {
    if (isset($variables['element']['#tooltip'])) {
        $variables['element']['#attributes']['data-toggle'] = 'tooltip';
        $tooltip = $variables['element']['#tooltip'];
        is_array($tooltip) or $tooltip = ['title' => $tooltip];
        empty($tooltip['title']) or $variables['element']['#attributes']['title'] = $tooltip['title'];
        empty($tooltip['placement']) or $variables['element']['#attributes']['data-placement'] = $tooltip['placement'];
    }
    sbadmin2_utils::preprocess_theme_wrapper($variables, 'input-group-addon');
}

/**
 * Implements template_preprocess_HOOK() for theme_sbadmin2_form_element().
 * @see: template_preprocess_menu_tree()
 */
function sbadmin2_preprocess_form_element2(&$variables) {
    // return;
    $variables['#element'] = $variables['element'];
    $variables['element'] = $variables['element']['#children'];
    $variables['description'] = isset($variables['#element']['#description']) ? $variables['#element']['#description'] : '';
}

function sbadmin2_preprocess_submit3(&$variables) {
    $element = &$variables['element'];
    $element['#attributes']['type'] = 'submit';
    element_set_attributes($element, array('id', 'name', 'value'));
    $element['#attributes']['class'][] = 'btn';
    $element['#attributes']['class'][] = 'btn-default';
    if (!empty($element['#attributes']['disabled'])) {
        $element['#attributes']['class'][] = 'form-button-disabled';
    }
    // Move value.
    $element['#children'] = $element['#attributes']['value'];
    unset($element['#attributes']['value']);
    // Path.
    if (isset($element['#path'])) {
        $element['#attributes']['onclick'] = "window.location.href='".$element['#path']."'";
        $element['#attributes']['type'] = 'button';
        unset($element['#attributes']['name']);
    }
    sbadmin2_utils::preprocess_theme_wrapper($variables);
}

// Theme function.

/**
 *
 */
function sbadmin2_textfield2($variables) {
    $variables['element']['#attributes']['class'][] = 'form-control';
    if (isset($variables['element']['#title'])) {
        $variables['element']['#attributes']['placeholder'] = $variables['element']['#title'];
        $variables['element']['#title'] = '';
    }
    return theme_textfield($variables);
}

/**
 *
 */
function sbadmin2_password2($variables) {
    $variables['element']['#attributes']['class'][] = 'form-control';
    if (isset($variables['element']['#title'])) {
        $variables['element']['#attributes']['placeholder'] = $variables['element']['#title'];
        $variables['element']['#title'] = '';
    }
    return theme_password($variables);
}

function sbadmin2_submit2($variables) {
    return isset($variables['element']['#value']) ? $variables['element']['#value'] : '';
}

function sbadmin2_icon($variables) {
    $element = $variables['element'];
    $bundle = isset($element['#bundle']) ? $element['#bundle'] : 'fontawesome';
    $icon = isset($element['#icon']) ? $element['#icon'] : '';
    $attributes = [];
    switch ($bundle) {
        case 'glyphicon':
            $attributes['class'][] = 'icon';
            $attributes['class'][] = 'glyphicon';
            empty($element['#icon']) or $attributes['class'][] = 'glyphicon-' . $element['#icon'];
            break;

        case 'fontawesome':
            $attributes['class'][] = 'fa';
            $attributes['class'][] = 'fa-fw';
            empty($element['#icon']) or $attributes['class'][] = 'fa-' . $element['#icon'];
            break;

        default:
            // Do something.
            break;
    }
    return '<span aria-hidden="true"' . drupal_attributes($attributes) . '></span>';
}

function sbadmin2_menu_nolink(&$variables) {
    sbadmin2_utils::remove_drupal_class($variables['element']);
    $element = $variables['element'];
    $sub_menu = '';
    if ($element['#below']) {
        $sub_menu = drupal_render($element['#below']);
    }
    $element['#localized_options']['external'] = true;
    $output = l($element['#title'], 'javascript:void(0)', $element['#localized_options']);
    return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}