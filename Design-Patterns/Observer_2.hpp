#pragma once
#include "Print.hpp"
#include <iostream>
#include <list>
#include <string>

// Concept From: Head First Design Patterns
// Example in C++ written by: Paul Burgess

// The observer pattern defines a one-to-many relationship.  When the subject
// changes state, the observers (dependents) are notified.

// This observer pattern using raw pointers.


// ------ Observer (the "many" in the one-to-many) relationship ------
class IObserverRaw {
public:
	virtual ~IObserverRaw() = default;
	virtual void update() = 0;
};


// ------ Subject (the "one" in the one-to-many) relationship ------
class ISubjectRaw {
public:
	virtual ~ISubjectRaw() = default;
	virtual void register_observer(IObserverRaw* observer) = 0;
	virtual void remove_observer(IObserverRaw* observer) = 0;
	virtual void notify_observers() const = 0;
};


// ------------------------- Interfaces -------------------------
class IDisplayElementRaw {
public:
	virtual ~IDisplayElementRaw() = default;
	virtual void display() const = 0;
};

class IWeatherDataGetterRaw {
public:
	virtual ~IWeatherDataGetterRaw() = default;
	virtual float get_temperature() const = 0;
	virtual float get_humidity() const = 0;
	virtual float get_pressure() const = 0;
};


// --------------------- Concrete Classes ---------------------
class WeatherDataFromDBRaw : public IWeatherDataGetterRaw {
public:
	float get_temperature() const override {
		return 91.50f;
	}
	float get_humidity() const override {
		return 37.45f;
	}
	float get_pressure() const override {
		return 88.74f;
	}
};


// ------------------------ Subject (the "one") ------------------------
class WeatherDataSubjectRaw : public ISubjectRaw {

public:
	WeatherDataSubjectRaw(const IWeatherDataGetterRaw* weather_data_getter)
		:m_temperature{ weather_data_getter->get_temperature() },
		m_humidity{ weather_data_getter->get_humidity() },
		m_pressure{ weather_data_getter->get_pressure() },
		m_weather_data_getter{ weather_data_getter }{
	}

	void register_observer(IObserverRaw* observer) override {
		m_observer_list.push_back(observer);
	}

	void remove_observer(IObserverRaw* observer) override {
		m_observer_list.remove(observer);
	}

	void notify_observers() const override {
		for (const auto& observer : m_observer_list) {
			observer->update();
		}
	}

	void set_measurements() {
		m_temperature = m_weather_data_getter->get_temperature();
		m_humidity = m_weather_data_getter->get_humidity();
		m_pressure = m_weather_data_getter->get_pressure();
		notify_observers();
	}

	float get_temperature() const {
		return m_temperature;
	}

	float get_humidity() const {
		return m_humidity;
	}

	float get_pressure() const {
		return m_pressure;
	}

private:
	float m_temperature;
	float m_humidity;
	float m_pressure;

	std::list<IObserverRaw*> m_observer_list;
	const IWeatherDataGetterRaw* m_weather_data_getter;

};


// --------------------- Observer (part of the "many") ---------------------
class CurrentConditionsDisplayRaw : public IDisplayElementRaw, public IObserverRaw {

public:
	CurrentConditionsDisplayRaw(WeatherDataSubjectRaw* weather_data_subject)
		:m_temperature{ weather_data_subject->get_temperature() },
		m_pressure{ weather_data_subject->get_pressure() },
		m_humidity{ weather_data_subject->get_humidity() },
		m_weather_data_subject{ weather_data_subject }{

		m_weather_data_subject->register_observer(this);
	}

	void display() const override {
		print("Temperature: " + std::to_string(m_temperature));
		print("Humidity: " + std::to_string(m_humidity));
		print("Pressure: " + std::to_string(m_pressure));
	}

	void update() override {
		m_temperature = m_weather_data_subject->get_temperature();
		m_humidity = m_weather_data_subject->get_humidity();
		m_pressure = m_weather_data_subject->get_pressure();
	}

private:
	float m_temperature;
	float m_pressure;
	float m_humidity;
	WeatherDataSubjectRaw* m_weather_data_subject;

};


// --------------------- Observer (part of the "many") ---------------------
class FutureConditionsDisplayRaw : public IDisplayElementRaw, public IObserverRaw {

public:
	FutureConditionsDisplayRaw(WeatherDataSubjectRaw* weather_data_subject)
		:m_temperature{ 0.0f },
		m_pressure{ 0.0f },
		m_humidity{ 0.0f },
		m_weather_data_subject(weather_data_subject){

		m_weather_data_subject->register_observer(this);
	}

	void update() override {
		m_temperature = m_weather_data_subject->get_temperature();
		m_pressure = m_weather_data_subject->get_pressure();
		m_humidity = m_weather_data_subject->get_humidity();
	}

	void display() const override {
		print("Future forecast");
		print("Forecast Temperature: " + std::to_string(m_temperature + 5));
		print("Forecast Humidity: " + std::to_string(m_humidity + 1));
		print("Forecast Pressure: " + std::to_string(m_pressure + 3));
	}

private:
	float m_temperature;
	float m_pressure;
	float m_humidity;
	WeatherDataSubjectRaw* m_weather_data_subject;

};


// ---------------- Example ----------------
inline void show_display(const IDisplayElementRaw* display_element) {
	display_element->display();
}

inline void observer_2() {

	// Weather Subject
	IWeatherDataGetterRaw* weather_data_getter = new WeatherDataFromDBRaw;
	WeatherDataSubjectRaw* weather_data_subject = new WeatherDataSubjectRaw{ weather_data_getter };

	// Create display element and register the with element with the weather_data_subject
	CurrentConditionsDisplayRaw* current_conditions_display_element = new CurrentConditionsDisplayRaw{ weather_data_subject };
	FutureConditionsDisplayRaw* future_conditions_display_element = new FutureConditionsDisplayRaw(weather_data_subject);

	// Update weather and notify all observers
	weather_data_subject->set_measurements();

	// Display weather
	show_display(current_conditions_display_element);
	show_display(future_conditions_display_element);

	// Cleanup
	delete weather_data_getter;
	delete weather_data_subject;
	delete current_conditions_display_element;
	delete future_conditions_display_element;

}