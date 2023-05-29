// Ultrasound pins for Obstacle distance Calculation
int trigObstaclePin = 9;
int echoObstaclePin = 10;
int ledObstacle = 3;

// Ultrasound pins for Depth distance Calculation
int trigDepthPin = 6;
int echoDepthPin = 5;
int ledDepth = 11;

// Active Buzzer pin for sound alarm
int soundPin = 12;

// Min Depth or Max obstacle detection range
int alarmThreeshold = 30;

// Keep track of the time it takes for the ping to go and come back (using pulseIn)
long obstacleDuration;
long depthDuration;

long obstacleDistance;
long depthDistance;

void setup() {
  Serial.begin(9600);
  pinMode(trigObstaclePin, OUTPUT);
  pinMode(echoObstaclePin, INPUT);
  pinMode(ledObstacle, OUTPUT);
  pinMode(ledDepth, OUTPUT);
  pinMode(trigDepthPin, OUTPUT);
  pinMode(echoDepthPin, INPUT);
  pinMode(soundPin, OUTPUT);
}

void loop() {

  digitalWrite(trigObstaclePin, LOW);
  digitalWrite(trigObstaclePin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigObstaclePin, LOW);
  // Get timing (in microseconds) when the echo went high, then stop when it went low
  obstacleDuration = pulseIn(echoObstaclePin, HIGH);


  //Sound travels 34300 cms every 100000 μs (microsecond)
  //That means that it moves 29 cm every 1 μs
  //Divide duration by 29, but then by half (because it's travelling from and to)
  obstacleDistance = obstacleDuration / 58.0;


  if (obstacleDistance < 30) {
    digitalWrite(ledObstacle, HIGH);
    int soundDelay = soundDelayForObstacle(obstacleDistance);
    digitalWrite(soundPin, HIGH);
    delay(soundDelay);
    digitalWrite(soundPin, LOW);
    delay(1);
  } else {
    digitalWrite(ledObstacle, LOW);
  }


  digitalWrite(trigDepthPin, LOW);
  digitalWrite(trigDepthPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigDepthPin, LOW);
  // Get timing (in microseconds) when the echo went high, then stop when it went low
  depthDuration = pulseIn(echoDepthPin, HIGH);


  //Sound travels 34300 cms every 100000 μs (microsecond)
  //That means that it moves 29 cm every 1 μs
  //Divide duration by 29, but then by half (because it's travelling from and to)
  depthDistance = depthDuration / 58.0;


  if (depthDistance > 25) {
    digitalWrite(ledDepth, HIGH);
    int soundDelay = soundDelayForDepth(depthDistance);
    digitalWrite(soundPin, HIGH);
    delay(soundDelay);
    digitalWrite(soundPin, LOW);
    delay(1);
  } else {
    digitalWrite(ledDepth, LOW);
  }

}



int soundDelayForObstacle(long distance) {
  int delay;
  if (distance > alarmThreeshold) {
    delay = 1000;
  }
  if (distance <= alarmThreeshold) {
    delay = 600;
  }
  if (distance <= 20) {
    delay = 300;
  }
  if (distance <= 10) {
    delay = 100;
  }

  return delay;
}

int soundDelayForDepth(long distance) {
  int delay;
  if (distance > alarmThreeshold) {
    delay = 100;
  }
  if (distance <= alarmThreeshold) {
    delay = 300;
  }
  if (distance <= 20) {
    delay = 600;
  }
  if (distance <= 10) {
    delay = 1000;
  }

  return delay;
}
