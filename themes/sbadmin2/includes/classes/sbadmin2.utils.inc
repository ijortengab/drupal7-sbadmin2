<?php

class sbadmin2_utils
{
    /**
     *
     */
    public static function remove_theme_wrappers($hook, &$element)
    {
        if (isset($element['#theme_wrappers']) && in_array($hook, $element['#theme_wrappers'])) {
            $key = array_search($hook, $element['#theme_wrappers']);
            unset($element['#theme_wrappers'][$key]);
        }
    }

    /**
     *
     */
    public static function replace_theme_wrappers($find, $replace, &$element)
    {
        if (isset($element['#theme_wrappers']) && in_array($find, $element['#theme_wrappers'])) {
            $key = array_search($find, $element['#theme_wrappers']);
            $element['#theme_wrappers'][$key] = $replace;
        }
    }

    /**
     *
     */
    public static function prepend_theme_wrappers($hook, &$element)
    {
        isset($element['#theme_wrappers']) or $element['#theme_wrappers'] = array();
        array_unshift($element['#theme_wrappers'], $hook);
    }

    /**
     *
     */
    public static function remove_drupal_class(&$element)
    {
        foreach (['first', 'last', 'leaf', 'active-trail', 'expanded'] as $class) {
            if (in_array($class, $element['#attributes']['class'])) {
                $key = array_search($class, $element['#attributes']['class']);
                unset($element['#attributes']['class'][$key]);
            }
        }
    }

    /**
     * Common Preprocess for theme_wrapper.
     * - Menyediakan variables $attributes dan $element untuk template.
     * - Menambah class dengan cepat.
     */
    public static function preprocess_theme_wrapper(&$variables, $additional_class = null)
    {
        $additional_class === null or $variables['element']['#attributes']['class'][] = $additional_class;
        $variables['attributes'] = isset($variables['element']['#attributes']) ? $variables['element']['#attributes'] : [];
        $variables['attributes'] = drupal_attributes($variables['attributes']);
        $variables['element'] = $variables['element']['#children'];
    }
}