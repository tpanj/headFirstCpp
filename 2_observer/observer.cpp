/*
 * observer.cpp
 *
 *  Created on: 3. feb. 2015
 *      Author: Tadej Panjtar
 */
#include <iostream>
#include <list>

using namespace std;

class Observer {
public: virtual void update(float, float, float) = 0;
virtual ~Observer() {}
};
class DisplayElement {
public: virtual void display() = 0;
virtual ~DisplayElement() {}
};
class Subject {
protected:
    list<Observer *> observers;
public:
    virtual void registerObserver(Observer *o) = 0;
    virtual void removeObserver(Observer *o) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() {}
};
class WeatherData: public Subject {
private:
    float temperature, humidity, pressure;
public:
    virtual void registerObserver(Observer * o) { observers.push_back(o); }
    virtual void removeObserver(Observer * o) { observers.remove(o); }
    virtual void notifyObservers() {
        for(list<Observer *>::iterator it =observers.begin(); it != observers.end(); it++)
            (*it)->update(temperature, humidity, pressure);
    }
    void measurementsChanged() {
        notifyObservers();
    }
    void setMeasurements(float temp, float hum, float press) {
        this->temperature = temp;
        this->humidity = hum;
        this->pressure = press;
        measurementsChanged();
    }
};
struct CurrentConditionsDisplay: Observer, DisplayElement {
    CurrentConditionsDisplay(Subject * s):pressure(0.0), temperature(0.0), humidity(0.0) {
        weatherData = s;
        weatherData->registerObserver(this);
    }
    virtual void update(float temp, float hum, float press) {
        temperature = temp;
        humidity = hum;
        display();
    }
    virtual void display() {
        cout << "Current conditions: " << temperature <<
                "F degrees and " << humidity << "% humidity" << endl;
    }
private:
    float temperature, humidity, pressure;
    Subject *weatherData;
};

class ForecastDisplay: public Observer, public DisplayElement {
    float currentPressure, lastPressure;
    Subject *weatherData;
public:
    ForecastDisplay(Subject * s):currentPressure(0),lastPressure(0)
            { weatherData = s; weatherData->registerObserver(this); }
    virtual void update(float temp, float hum, float press) {
        lastPressure = currentPressure;
        currentPressure = press;
        display();
    }
    virtual void display() {
        cout << "Forecast: ";
        if (currentPressure>lastPressure) cout << "Improving weather on the way!" << endl;
        else if (currentPressure == lastPressure) cout << "More of the same" << endl;
        else  cout << "Watch out for cooler, rainy weather" << endl;
    }
    ~ForecastDisplay() { weatherData->removeObserver(this); } // Watch out !!!!! MANDATORY

};

/**
 *  OBSERVER PATTERN: defines a one-to-many dependency between objects so that when one
 *  object changes state, all its dependents are modified and updated automatically.
 */
int main()
{
    WeatherData *w = new WeatherData;
    CurrentConditionsDisplay *cd = new CurrentConditionsDisplay(w);
    CurrentConditionsDisplay *cd2 = new CurrentConditionsDisplay(w);
    ForecastDisplay *fd = new ForecastDisplay(w);
    w->setMeasurements(80.0, 65.0, 30.4);
    w->removeObserver(cd2);
    w->setMeasurements(82.0, 70.0, 29.2);
//  delete fd; // see MANDATORY
    w->setMeasurements(78.0, 90.0, 29.2);
/* OUT:
    Current conditions: 80F degrees and 65% humidity
    Current conditions: 80F degrees and 65% humidity
    Forecast: Improving weather on the way!
    Current conditions: 82F degrees and 70% humidity
    Forecast: Watch out for cooler, rainy weather
    Current conditions: 78F degrees and 90% humidity
    Forecast: More of the same
*/
}
