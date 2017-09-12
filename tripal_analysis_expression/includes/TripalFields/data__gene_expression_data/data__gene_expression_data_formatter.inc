<?php

/**
 * @class
 * Purpose:
 *
 * Display:
 * Configuration:
 */
class data__gene_expression_data_formatter extends ChadoFieldFormatter {

  // The default label for this field.
  public static $default_label = 'Expression';

  // The list of field types for which this formatter is appropriate.
  public static $field_types = ['data__gene_expression_data'];

  // The list of default settings for this formatter.
  public static $default_settings = [
    'setting1' => 'default_value',
  ];

  /**
   * Provides the field's setting form.
   *
   * This function corresponds to the hook_field_formatter_settings_form()
   * function of the Drupal Field API.
   *
   * The settings form appears on the 'Manage Display' page of the content
   * type administration page. This function provides the form that will
   * appear on that page.
   *
   * To add a validate function, please create a static function in the
   * implementing class, and indicate that this function should be used
   * in the form array that is returned by this function.
   *
   * This form will not be displayed if the formatter_settings_summary()
   * function does not return anything.
   *
   * param $field
   *   The field structure being configured.
   * param $instance
   *   The instance structure being configured.
   * param $view_mode
   *   The view mode being configured.
   * param $form
   *   The (entire) configuration form array, which will usually have no use
   *   here.  Typically for reference only.
   * param $form_state
   *   The form state of the (entire) configuration form.
   *
   * @return
   *   A Drupal Form array containing the settings form for this field.
   */
  public function settingsForm($view_mode, $form, &$form_state) {

  }

  /**
   *  Provides the display for a field
   *
   * This function corresponds to the hook_field_formatter_view()
   * function of the Drupal Field API.
   *
   *  This function provides the display for a field when it is viewed on
   *  the web page.  The content returned by the formatter should only include
   *  what is present in the $items[$delta]['values] array. This way, the
   *  contents that are displayed on the page, via webservices and downloaded
   *  into a CSV file will always be identical.  The view need not show all
   *  of the data in the 'values' array.
   *
   * @param $element
   * @param $entity_type
   * @param $entity
   * @param $langcode
   * @param $items
   * @param $display
   *
   * @return void
   *    An element array compatible with that returned by the
   *    hook_field_formatter_view() function.
   */
  public function view(&$element, $entity_type, $entity, $langcode, $items, $display) {
    $field = 'data__gene_expression_data';
    $variables = $entity->{$field}['und'][0];
    $content = '';

    if (!$variables['has_exp'] && $variables['json_exp']) {
      $content = 'No biomaterial libraries express this feature.';
    }
    elseif ($variables['json_exp']) {
      drupal_add_css(drupal_get_path('module', 'tripal_analysis_expression') . '/theme/css/expression.css');
      drupal_add_js(drupal_get_path('module', 'tripal_analysis_expression') . '/theme/js/expression.js');

      $num_of_analyses = count($variables['analyses']);
      if ($num_of_analyses > 1) {
        $content .= '<h3>Available Expression Analyses</h3>';
        $rows = [];
        foreach ($variables['analyses'] as $analysis) {
          $rows[] = [l($analysis->name, $analysis->url)];
        }

        $content .= theme('table', [
          'header' => [],
          'rows' => $rows,
        ]);
      }
      elseif ($num_of_analyses === 1) {
        $content .= '<h3>Available Expression Analyses</h3>';
        $analysis = current($variables['analyses']);
        $content .= '<p>' . l($analysis->name, $analysis->url) . '</p>';
      }

      $content .= '
            <h3>Expression Heat Map</h3>
            <p>
              Hover the mouse over a column in the graph to view expression values.
            </p>
            <p>
              <a href="javascript:;" onclick="expSortDown()">Sort Descending</a> |
              <a href="javascript:;" onclick="expSortUp()">Sort Ascending</a> |
              <a href="javascript:;" onclick="nonZero()">Only Non-Zero Values</a> |
              <a href="javascript:;" onclick="expChart()">Tile/Chart</a> |
              <a href="javascript:;" onclick="expNormal()">Reset</a>
            </p>
            ';

      tripal_add_d3js();
      $hide_biomaterial_labels = $variables['hide_biomaterial_labels'];
      $json_exp = $variables['json_exp'];
      $limit_label_length = $variables['limit_label_length'];
      $expression_display = $variables['expression_display'];
      $biomaterial_display_width = $variables['biomaterial_display_width'];

      $content .= '<script type="text/javascript">
            var heatMapRaw=' . $json_exp . '
            var maxLength=' . $limit_label_length . '
            var showLabels=' . $hide_biomaterial_labels . '
            var col="' . $expression_display . '"
            var colWidth=' . $biomaterial_display_width . '
            Drupal.behaviors.tripal_analysis_expression = {
              attach: function (context, settings) {
                var $ = jQuery;
                expNormal();
                $(document).on("tripal_ds_pane_expanded", function(event) {
                    if($(event.id).text().indexOf("Hover the mouse over a column in the graph to view expression values") > -1) {
                      expNormal();
                    }
                });
              }
            };
          </script>
          <figure></figure>
          <a href="#expression-top">back to top</a>';
    }
    else {
      $content = 'No biomaterial libraries express this feature.';
    }

    $element[] = [
      '#type' => 'markup',
      '#markup' => $content,
    ];
  }

  /**
   * Provides a summary of the formatter settings.
   *
   * This function corresponds to the hook_field_formatter_settings_summary()
   * function of the Drupal Field API.
   *
   * On the 'Manage Display' page of the content type administration page,
   * fields are allowed to provide a settings form.  This settings form can
   * be used to allow the site admin to define how the field should be
   * formatted.  The settings are then available for the formatter()
   * function of this class.  This function provides a text-based description
   * of the settings for the site developer to see.  It appears on the manage
   * display page inline with the field.  A field must always return a
   * value in this function if the settings form gear button is to appear.
   *
   * See the hook_field_formatter_settings_summary() function for more
   * information.
   *
   * @param $field
   * @param $instance
   * @param $view_mode
   *
   * @return string
   *   A string that provides a very brief summary of the field settings
   *   to the user.
   *
   */
  public function settingsSummary($view_mode) {
    return '';
  }
}