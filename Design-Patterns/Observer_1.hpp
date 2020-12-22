#pragma once
#include "Print.hpp"
#include <list>
#include <string>
#include <vector>
#include <memory>

// Concept From: Head First Design Patterns
// Example in C++ written by: Paul Burgess

// The observer pattern defines a one-to-many relationship.  When the subject
// changes state, the observers (dependents) are notified.

// This observer pattern using smart pointers.  The raw pointer example
// does the same thing as this, but is easier to follow.


// ------ Observer (the "many" in the one-to-many) relationship ------
class IObserver {
public:
	IObserver() = default;
	virtual ~IObserver() = default;

	// The register_self() function is necessary when working with smart
	// pointers.  Shared pointers need to be created before using 'this'
	// operator.  See raw pointer example for registration within the
	// constructor

	virtual void register_self() = 0;
	virtual void update() = 0;
};


// ------ Subject (the "one" in the one-to-many) relationship ------
class ISubject {

public:
	ISubject() = default;
	virtual ~ISubject() = default;

	virtual void register_observer(const std::shared_ptr<IObserver>& observer_ptr) = 0;
	virtual void remove_observer(const std::shared_ptr<IObserver>& observer_ptr) = 0;
	virtual void notify_all_observers() const = 0;
};


// ------------------------- Interfaces -------------------------
class IDisplayElement {
public:
	IDisplayElement() = default;
	virtual ~IDisplayElement() = default;
	virtual void display() const = 0;
};

class IWeatherDataGetter {
public:
	IWeatherDataGetter() = default;
	virtual ~IWeatherDataGetter() = default;
	virtual float get_temperature() const = 0;
	virtual float get_humidity() const = 0;
	virtual float get_pressure() const = 0;
};


// --------------------- Concrete Classes ---------------------
class WeatherDataFromDB : public IWeatherDataGetter {
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
class WeatherDataSubject : public ISubject {

public:
	WeatherDataSubject(const std::shared_ptr<IWeatherDataGetter>& weather_getter)
		:m_current_temperature{ 0.0f },
		m_current_humidity{ 0.0f },
		m_current_pressure{ 0.0f },
		m_weather_getter_ptr{ weather_getter }{
	}

	void register_observer(const std::shared_ptr<IObserver>& observer_ptr) override {
		m_observer_list.push_back(observer_ptr);
	}

	void remove_observer(const std::shared_ptr<IObserver>& observer_ptr) override {
		m_observer_list.remove(observer_ptr);
	}

	void set_measurements() {
		m_current_temperature = m_weather_getter_ptr->get_temperature();
		m_current_humidity = m_weather_getter_ptr->get_humidity();
		m_current_pressure = m_weather_getter_ptr->get_pressure();
		notify_all_observers();
	}

	void notify_all_observers() const override {
		for (auto& observer : m_observer_list) {
			observer->update();
		}
	}

	float get_temperature() const {
		return m_current_temperature;
	}

	float get_humidity() const {
		return m_current_humidity;
	}

	float get_pressure() const {
		return m_current_pressure;
	}


private:
	float m_current_temperature;
	float m_current_humidity;
	float m_current_pressure;

	std::list<std::shared_ptr<IObserver>> m_observer_list;
	const std::shared_ptr<IWeatherDataGetter> m_weather_getter_ptr;
};


// --------------------- Observer (part of the "many") ---------------------
class CurrentConditionsDisplay : public IObserver, public IDisplayElement, public std::enable_shared_from_this<CurrentConditionsDisplay> {

public:
	CurrentConditionsDisplay(std::shared_ptr<WeatherDataSubject>& weather_data_subject_ptr)
		:m_current_temperature{ weather_data_subject_ptr->get_temperature() },
		m_current_humidity{ weather_data_subject_ptr->get_humidity() },
		m_current_pressure{ weather_data_subject_ptr->get_pressure() },
		m_weather_data_subject_ptr{ weather_data_subject_ptr }{
	}

	~CurrentConditionsDisplay() = default;

	void register_self() override {
		m_weather_data_subject_ptr->register_observer(shared_from_this());
	}

	void update() override {
		m_current_temperature = m_weather_data_subject_ptr->get_temperature();
		m_current_humidity = m_weather_data_subject_ptr->get_humidity();
		m_current_pressure = m_weather_data_subject_ptr->get_pressure();
	}

	void display() const override {
		print("Temperature: " + std::to_string(m_current_temperature));
		print("Humidity: " + std::to_string(m_current_humidity));
		print("Pressure: " + std::to_string(m_current_pressure));
	}

private:
	float m_current_temperature;
	float m_current_humidity;
	float m_current_pressure;
	std::shared_ptr<WeatherDataSubject> m_weather_data_subject_ptr;

};


// --------------------- Observer (part of the "many") ---------------------
class ForecastConditionsDisplay : public IObserver, public IDisplayElement, public std::enable_shared_from_this<ForecastConditionsDisplay> {

public:
	ForecastConditionsDisplay(const std::shared_ptr<WeatherDataSubject>& weather_data_subject_ptr)
		:m_current_temperature{ weather_data_subject_ptr->get_temperature() },
		m_current_humidity{ weather_data_subject_ptr->get_humidity() },
		m_current_pressure{ weather_data_subject_ptr->get_pressure() },
		m_weather_data_subject_ptr{ weather_data_subject_ptr }{
	}

	~ForecastConditionsDisplay() = default;;

	void register_self() override {
		m_weather_data_subject_ptr->register_observer(shared_from_this());
	}

	void update() override {
		m_current_temperature = m_weather_data_subject_ptr->get_temperature();
		m_current_humidity = m_weather_data_subject_ptr->get_humidity();
		m_current_pressure = m_weather_data_subject_ptr->get_pressure();
	}

	void display() const override {
		print("Forecast Temperature: " + std::to_string(m_current_temperature + 5));
		print("Forecast Humidity: " + std::to_string(m_current_humidity + 1));
		print("Forecast Pressure: " + std::to_string(m_current_pressure + 3));
	}

private:
	float m_current_temperature;
	float m_current_humidity;
	float m_current_pressure;
	std::shared_ptr<WeatherDataSubject> m_weather_data_subject_ptr;

};


// ---------------- Example ----------------
inline void display_weather_observer(std::vector<std::shared_ptr<IDisplayElement>>& display_elements) {
	for (const auto& element : display_elements) {
		element->display();
		print("----------------");
	}
}

inline void observer_1() {

	// Get weather data from db store in WeatherDataSubject
	std::shared_ptr<IWeatherDataGetter> weather_getter_ptr = std::make_shared<WeatherDataFromDB>();
	std::shared_ptr<WeatherDataSubject> weather_data_subject_ptr = std::make_shared<WeatherDataSubject>(weather_getter_ptr);

	// Create Observer and store pointer to WeatherDataSubject (allows us to register the observer and access data)	
	std::shared_ptr<CurrentConditionsDisplay> current_conditions_display_ptr = std::make_shared<CurrentConditionsDisplay>(weather_data_subject_ptr);
	current_conditions_display_ptr->register_self();

	std::shared_ptr<ForecastConditionsDisplay> forecast_conditions_display_ptr = std::make_shared<ForecastConditionsDisplay>(weather_data_subject_ptr);
	forecast_conditions_display_ptr->register_self();

	// Get weather data and notify all observers	
	weather_data_subject_ptr->set_measurements();

	// Store display elements
	std::vector<std::shared_ptr<IDisplayElement>> display_elements;
	display_elements.push_back(current_conditions_display_ptr);
	display_elements.push_back(forecast_conditions_display_ptr);

	// Display updated data
	display_weather_observer(display_elements);

}