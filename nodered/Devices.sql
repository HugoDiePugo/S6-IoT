-- phpMyAdmin SQL Dump
-- version 5.2.3
-- https://www.phpmyadmin.net/
--
-- Host: mysql
-- Gegenereerd op: 24 mrt 2026 om 15:29
-- Serverversie: 9.6.0
-- PHP-versie: 8.3.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `public`
--

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `Devices`
--

CREATE TABLE `Devices` (
  `deviceeui` varchar(255) DEFAULT NULL,
  `latitude` decimal(10,6) NOT NULL,
  `longitude` decimal(10,6) NOT NULL,
  `threshold_co2` decimal(10,2) DEFAULT NULL,
  `threshold_battery` decimal(10,3) DEFAULT NULL,
  `threshold_humidity` decimal(10,2) DEFAULT NULL,
  `threshold_temperature` decimal(10,2) DEFAULT NULL,
  `max_rate_of_change_co2` decimal(10,2) DEFAULT NULL,
  `max_rate_of_change_battery` decimal(10,3) DEFAULT NULL,
  `max_rate_of_change_humidity` decimal(10,2) DEFAULT NULL,
  `max_rate_of_change_temperature` decimal(10,2) DEFAULT NULL,
  `sample_period` int NOT NULL,
  `health_update_period` int NOT NULL,
  `battery_alarm_period` int NOT NULL,
  `temperature_alarm_period` int NOT NULL,
  `humidity_alarm_period` int NOT NULL,
  `co2_alarm_period` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Gegevens worden geëxporteerd voor tabel `Devices`
--

INSERT INTO `Devices` (`deviceeui`, `latitude`, `longitude`, `threshold_co2`, `threshold_battery`, `threshold_humidity`, `threshold_temperature`, `max_rate_of_change_co2`, `max_rate_of_change_battery`, `max_rate_of_change_humidity`, `max_rate_of_change_temperature`, `sample_period`, `health_update_period`, `battery_alarm_period`, `temperature_alarm_period`, `humidity_alarm_period`, `co2_alarm_period`) VALUES
('0004A30B00203D94', 51.988913, 5.948561, 1100.00, 2.800, 30.00, 50.00, 30.00, 1.000, 20.00, 5.00, 1, 2, 10, 1, 2, 1),
('0004A30B001EA0EB', 52.049560, 6.312559, 1100.00, 2.800, 30.00, 50.00, 30.00, 1.000, 20.00, 5.00, 1, 2, 1, 1, 1, 1);

--
-- Indexen voor geëxporteerde tabellen
--

--
-- Indexen voor tabel `Devices`
--
ALTER TABLE `Devices`
  ADD UNIQUE KEY `devices_unique` (`deviceeui`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
