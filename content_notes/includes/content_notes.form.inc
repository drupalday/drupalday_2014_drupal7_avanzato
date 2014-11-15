<?php
/**
 * @file
 * Contains form functions for module Content Notes.
 */

/**
 * Content Notes form.
 */
function content_notes_form($form, &$form_state, $nid) {
  $form_state['#nid'] = $nid;

  $form['note'] = array(
    '#title' => t('Write here your note'),
    '#type' => 'textarea',
    '#required' => TRUE
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save')
  );

  return $form;
}

/**
 * Submit callback.
 *
 * @see content_notes_form().
 */
function content_notes_form_submit($form, &$form_state) {
  $note = array(
    'nid' => $form_state['#nid'],
    'note' => $form_state['values']['note'],
  );

  content_notes_save($note);
}

/**
 * Content Notes edit form.
 */
function content_notes_edit_form($form, &$form_state, $note) {
  $form_state['#note'] = $note;

  $form['note'] = array(
    '#title' => t('Update your note'),
    '#type' => 'textarea',
    '#default_value' => $note->note,
    '#required' => TRUE
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save')
  );

  return $form;
}

/**
 * Submit callback.
 *
 * @see content_notes_edit_form().
 */
function content_notes_edit_form_submit($form, &$form_state) {
  $note = $form_state['#note'];
  $note->note = $form_state['values']['note'];

  content_notes_save($note);

  $form_state['redirect'] = 'node/' . $note->nid;
}

/**
 * Content Notes delete confirm form.
 */
function content_notes_delete_confirm($form, &$form_state, $note) {
  $form['#note'] = $note;

  $form['id'] = array(
    '#type' => 'value',
    '#value' => $note->id
  );

  $form['note'] = array(
    '#type' => 'item',
    '#markup' => $note->note
  );

  return confirm_form($form,
    t('Are you sure you want to delete this note?'),
    'node/' . $note->nid,
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Executes note deletion.
 *
 * @see content_notes_delete_confirm()
 */
function content_notes_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $note = $form['#note'];
    content_notes_delete($note->id);
    drupal_set_message(t('Note with id %id has been deleted.', array('%id' => $note->id)));
  }

  $form_state['redirect'] = 'node/' . $note->nid;
}