<?php

/**
 * Provides integration with Sphinx 2.x.
 */
class SearchlightBackendSphinx2 extends SearchlightBackendSphinx {

  /**
   * Constructor.
   */
  function __construct($id) {
    parent::__construct($id);

    $this->lib_name = 'sphinx2';
    $this->file_path = 'sphinxapi.php';
  }

  /**
   * Override of settingsForm().
   */
  function settingsForm() {
    $form = parent::settingsForm();

    // Library.
    $form['library'] = $this->libraryStatusForm(l('Sphinx 2.0.1-beta downloads', 'http://sphinxsearch.com/downloads/beta/'));

    return $form;
  }

}
