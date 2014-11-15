<?php

/**
 * @file
 * Contains administrative functions for module Content Notes.
 */

/**
 * Content Notes Settings form
 */
function content_notes_settings_form($form, &$form_state) {
  $form['content_notes'] = array(
    '#title' => t('Settings'),
    '#type' => 'fieldset',
  );

  $form['content_notes']['content_notes_enabled_types'] = array(
    '#title' => t('Enabled types'),
    '#type' => 'checkboxes',
    '#options' => _content_notes_get_types(),
    '#default_value' => variable_get('content_notes_enabled_types', array()),
    '#description' => t('Select content types enabled for Notes')
  );

  $form['content_notes']['content_notes_display_type'] = array(
    '#title' => t('Display type'),
    '#type' => 'radios',
    '#options' => array(
      'block' => t('Block'),
      'content' => t('Content'),
    ),
    'block' => array(
      '#description' => t('Display all notes of a node using a block')
    ),
    'content' => array(
      '#description' => t("Display all notes in directly in the content area. You'll be able to decide where to display your notes, using the manage display of content types.")
    ),
    '#default_value' => variable_get('content_notes_display_type', 'block')
  );

  return system_settings_form($form);
}

/**
 * Get an associative array of content types.
 * @return array
 */
function _content_notes_get_types() {
  $bundles = array();

  foreach (node_type_get_types() as $bundle) {
    $bundles[$bundle->type] = $bundle->name;
  }

  return $bundles;
}

function content_notes_list() {
  $header = array(t('Note'), t('Author'), t('Node'), t('Created'),  t('Changed'), t('Operations'));
  $rows = array();

  if ($notes = content_notes_get_all()) {
    foreach ($notes as $note) {
      $user = user_load($note->uid);
      $node = node_load($note->nid);
      $operations = array(
        'edit' => l(t('Edit'), 'admin/content/notes/' . $note->id . '/edit', array('query' => drupal_get_destination())),
        'delete' => l(t('Delete'), 'admin/content/notes/' . $note->id . '/delete', array('query' => drupal_get_destination())),
      );

      $rows[] = array(
        $note->note,
        l($user->name, 'user/' . $user->uid),
        l($node->title, 'node/' . $node->nid),
        format_date($note->created, 'short'),
        format_date($note->changed, 'short'),
        implode(' | ', $operations)
      );
    }
  }
  else {
    $rows[] = array(
      array(
        'data' => t('There are no notes.'),
        'colspan' => count($header),
        'align' => 'center'
      )
    );
  }

  return array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows
  );
}