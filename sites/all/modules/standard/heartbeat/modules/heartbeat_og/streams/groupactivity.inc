<?php

/**
 * @file
 *   Defines a stream for Group Activity.
 */

/**
 * Concrete class GroupActivity
 *   Defines a stream for activity within a group.
 */
class GroupActivity extends HeartbeatStream {

  protected $nid = 0;
  protected $og_context = NULL;
  protected $group = NULL;

  public function construct() {
    $this->detectGroup();
  }

  /**
   * detectGroup
   *
   * Detects the group for a given node ID.
   */
  private function detectGroup() {

    // Set the group via current group context.
    if ($og_context = og_context()) {
      $this->og_context = $og_context;
      $this->setGroup($og_context->etid);
    }

  }

  /**
   * setGroup
   *
   * Sets the group for a given node ID.
   * @param Integer $nid
   *   The group node ID.
   */
  private function setGroup($nid) {
    $this->nid = $nid;
    $this->group = node_load($this->nid);
  }

  /**
   * hasAccess
   *
   * @param $text
   * @return boolean to indicate the access to the stream
   */
  public function hasAccess() {
    return $this->nid > 0 ? TRUE : FALSE;
  }

  /**
   * Implementation of queryAlter().
   */
  protected function queryAlter() {

    $this->query->condition('ha.nid', 0, '<>');
    $this->query->condition('ha.in_group', 0, '>');
    $this->query->condition(db_or()
      ->condition('ha.nid', $this->nid)
      ->condition(db_and()->condition('ha.nid_target', $this->nid)->condition('ha.nid_target', 0, '>'))
    );

  }

}
