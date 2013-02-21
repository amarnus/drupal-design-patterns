<?php

// Like Drupal, here we assume that the event name (hook) is unique across the application.
function design_patterns_observer_mediator_page() {
  // Add a mediator.
  $mediator = new Mediator(new Logger());

  // Add a subject and register its events with the mediator.
  $subject = new Subject($mediator, array('item_create', 'item_read', 'item_update', 'item_delete'));

  // Create a few observers.
  $observer1 = new Observer('Observer 1');
  $observer2 = new Observer('Observer 2');

  // Register observers with mediator.
  $mediator->addObserver('item_create', $observer1);
  $mediator->addObserver(array('item_create', 'item_delete'), $observer2);

  // Logger
  $log = '';
  // Trigger event - Watch observers burn.
  $subject->triggerEvent('item_create'); 
  // Observer 1 says: I just observed item_create. 
  // Observer 2 says: I just observed item_create.
  $subject->triggerEvent('item_delete');
  // Observer 2 says: I just observed item_delete.

  return $mediator->logger->flush();
}

class Logger {

  private $log = '';

  public function log($message) {
    if (!empty($message)) {
      $this->log .= $message . '<br>';
    }
  }

  public function flush() {
    return $this->log;
  }

};

class Subject {
  private $observers = array();
  private $mediator;

  public function __construct(Mediator $mediator, $events = array()) {
    $this->mediator = $mediator;
    $this->events = $events;
    foreach ($this->events as $event) {
      $this->mediator->addEvent($event);
    }
  }

  public function triggerEvent($event) {
    $this->mediator->logger->log('Event ' . $event . ' triggered on the Subject.');
    $this->mediator->notify($event, $log);
  }
};

class Observer {
  private $name;

  public function __construct($name) {
    $this->name = $name;
  }

  public function notify($event, $logger) {
    return $logger->log($this->name . ' says: I just observed ' . $event  . '.');
  }
};

class Mediator {
  private $observer_map = array();
  public $logger;

  private function eventExists($event) {
    if (!isset($this->observer_map[$event])) {
      throw new Exception('Cannot bind to an invalid event.');
    }
    return TRUE;
  }

  public function __construct(Logger $logger) {
    $this->logger = $logger;
    $this->logger->log('Initialised a new Mediator.');
  }

  public function addEvent($event) {
    if (!isset($this->observer_map[$event])) {
      $this->observer_map[$event] = array();
      $this->logger->log('Event ' . $event . ' was registered with the Mediator.');
    }
  }

  public function addObserver($event, Observer $observer) {
    if (is_string($event)) {
      $events = array($event);
    }
    elseif (is_array($event)) {
      $events = $event;
    }
    foreach ($events as $event) {
      $this->eventExists($event);
      $this->observer_map[$event][] = $observer;
      $this->logger->log('An observer was registered for the event ' . $event . ' with the Mediator.');
    }
  }

  public function notify($event, &$log) {
    $this->eventExists($event);
    $this->logger->log('Observers for the event ' .  $event . ' are about to be notified.');
    foreach ($this->observer_map[$event] as $observer) {
      $this->logger->log($observer->notify($event, $this->logger));
    }
  }
};

