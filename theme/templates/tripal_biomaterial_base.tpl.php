<?php
  // This conditional is added to prevent errors in the biomaterial TOC admin page.
  if (property_exists($variables['node'],'biomaterial')) {
    $biomaterial = $variables['node']->biomaterial;
    $biomaterial = chado_expand_var($biomaterial, 'field', 'biomaterial.description');
    ?>

    <div class="tripal_biomaterial-data-block-desc tripal-data-block-desc"></div>

  <?php

  $headers = array();
  $rows = array();
 
  // The biomaterial name.
 
  $rows[] = array(
    array(
      'data' => 'Biomaterial',
      'header' => TRUE,
      'width' => '20%',
    ),
    '<i>' . $biomaterial->name . '</i>'
  );

  // The organism from which the biomaterial was collected
  if($biomaterial->taxon_id) {
    $rows[] = array(
      array(
        'data' => 'Organism',
        'header' => TRUE,
        'width' => '20%',
      ),
      '<i>' . $biomaterial->taxon_id->genus . ' ' . $biomaterial->taxon_id->species . ' (' . $biomaterial->taxon_id->common_name . ') ' . '</i>'
    );
  } 
 
  // The biosource provider
  if($biomaterial->taxon_id) {
    $rows[] = array(
      array(
        'data' => 'Biomaterial Provider',
        'header' => TRUE,
        'width' => '20%',
      ),
      '<i>' . $biomaterial->biosourceprovider_id->name . '</i>'
    );
  }

  // allow site admins to see the biomaterial ID
  if (user_access('view ids')) {
    // Biomaterial ID
    $rows[] = array(
      array(
        'data' => 'Biomaterial ID',
        'header' => TRUE,
        'class' => 'tripal-site-admin-only-table-row',
      ),
      array(
        'data' => $biomaterial->biomaterial_id,
        'class' => 'tripal-site-admin-only-table-row',
      ),
    );
  }

     // Generate the table of data provided above. 
    $table = array(
      'header' => $headers,
      'rows' => $rows,
      'attributes' => array(
        'id' => 'tripal_biomaterial-table-base',
        'class' => 'tripal-biomaterial-data-table tripal-data-table',
      ),
      'sticky' => FALSE,
      'caption' => '',
      'colgroups' => array(),
      'empty' => '',
    );

    // Print the table and the description.
    print theme_table($table); 

  // Print the biomaterial description.
  if ($biomaterial->description) { ?>
    <div style="text-align: justify"><?php print $biomaterial->description?></div> <?php
  }
 

  ?>


  <?php
  }
?>

