-- phpMyAdmin SQL Dump
-- version 5.0.3
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 22, 2021 at 09:46 AM
-- Server version: 10.4.14-MariaDB
-- PHP Version: 7.4.11

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `dbcrms`
--

-- --------------------------------------------------------

--
-- Table structure for table `admin`
--

CREATE TABLE `admin` (
  `admin_id` varchar(30) COLLATE utf8mb4_bin NOT NULL,
  `name` varchar(50) COLLATE utf8mb4_bin NOT NULL,
  `password` varchar(30) COLLATE utf8mb4_bin NOT NULL,
  `contact_num` varchar(50) COLLATE utf8mb4_bin NOT NULL,
  `email` varchar(50) COLLATE utf8mb4_bin NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `admin`
--

INSERT INTO `admin` (`admin_id`, `name`, `password`, `contact_num`, `email`) VALUES
('jae111', 'jaenee', '88998', '0177788987', 'jae@admin.com'),
('kenny112', 'kenny', '00000', '0187765467', 'kenny@admin.com'),
('linda98', 'linda', '09876', '0187776677', 'linda@admin.com'),
('wendylim', 'wendy', '88999', '0176677677', 'wendy@admin.com');

-- --------------------------------------------------------

--
-- Table structure for table `booking`
--

CREATE TABLE `booking` (
  `booking_id` varchar(20) COLLATE utf8mb4_bin NOT NULL,
  `rental_date` varchar(30) COLLATE utf8mb4_bin NOT NULL,
  `return_date` varchar(30) COLLATE utf8mb4_bin NOT NULL,
  `car_id` varchar(20) COLLATE utf8mb4_bin NOT NULL,
  `user_id` varchar(30) COLLATE utf8mb4_bin NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `booking`
--

INSERT INTO `booking` (`booking_id`, `rental_date`, `return_date`, `car_id`, `user_id`) VALUES
('B100', ' 7/1/2021', '9/1/2021', 'C000', 'mandydy'),
('B567', ' 21/1/2021', '22/1/2021', 'C123', ' xue123'),
('B765', ' 22/1/2021', '23/1/2021', 'C010', ' mandydy'),
('B777', ' 21/1/2021', '24/1/2021', 'C123', ' xue123');

-- --------------------------------------------------------

--
-- Table structure for table `car`
--

CREATE TABLE `car` (
  `car_id` varchar(20) COLLATE utf8mb4_bin NOT NULL,
  `brand` varchar(30) COLLATE utf8mb4_bin NOT NULL,
  `plate_num` varchar(20) COLLATE utf8mb4_bin NOT NULL,
  `numPassengers` int(11) NOT NULL,
  `price` double NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `car`
--

INSERT INTO `car` (`car_id`, `brand`, `plate_num`, `numPassengers`, `price`) VALUES
('C000', 'Produa Myvi', 'BGH1122', 5, 70),
('C010', 'Proton Alza', 'MDE7788', 7, 100),
('C123', 'Toyota Rush', 'AJJ7887', 7, 100),
('C999', 'Proton Saga', 'WTG1213', 5, 60);

-- --------------------------------------------------------

--
-- Table structure for table `feedback`
--

CREATE TABLE `feedback` (
  `feedback_id` varchar(30) COLLATE utf8mb4_bin NOT NULL,
  `rating` int(11) NOT NULL,
  `opinion` varchar(50) COLLATE utf8mb4_bin DEFAULT NULL,
  `booking_id` varchar(20) COLLATE utf8mb4_bin NOT NULL,
  `user_id` varchar(30) COLLATE utf8mb4_bin NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `feedback`
--

INSERT INTO `feedback` (`feedback_id`, `rating`, `opinion`, `booking_id`, `user_id`) VALUES
('F111', 10, 'Good service', 'B111', 'xue123'),
('F765', 8, 'Nice service', 'B765', 'mandydy');

-- --------------------------------------------------------

--
-- Table structure for table `payment`
--

CREATE TABLE `payment` (
  `payment_id` varchar(20) COLLATE utf8mb4_bin NOT NULL,
  `amount` double(6,2) NOT NULL,
  `accountNum` varchar(30) COLLATE utf8mb4_bin NOT NULL,
  `booking_id` varchar(20) COLLATE utf8mb4_bin NOT NULL,
  `user_id` varchar(30) COLLATE utf8mb4_bin NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `payment`
--

INSERT INTO `payment` (`payment_id`, `amount`, `accountNum`, `booking_id`, `user_id`) VALUES
('P100', 90.00, '899881777277', 'B613', 'mandydy'),
('P111', 200.00, '332223332333', 'B111', 'xue123'),
('P567', 200.00, '8788899988', 'B567', 'xue123'),
('P765', 60.00, '889988762778', 'B765', 'mandydy');

-- --------------------------------------------------------

--
-- Table structure for table `userdetail`
--

CREATE TABLE `userdetail` (
  `user_id` varchar(30) COLLATE utf8mb4_bin NOT NULL,
  `name` varchar(20) COLLATE utf8mb4_bin NOT NULL,
  `password` varchar(30) COLLATE utf8mb4_bin NOT NULL,
  `contact_num` varchar(30) COLLATE utf8mb4_bin NOT NULL,
  `address` varchar(50) COLLATE utf8mb4_bin NOT NULL,
  `email` varchar(50) COLLATE utf8mb4_bin NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `userdetail`
--

INSERT INTO `userdetail` (`user_id`, `name`, `password`, `contact_num`, `address`, `email`) VALUES
('azam', 'azam manu', '27667', '0198876278', 'Cheng', 'azam@user.com'),
('jen89', 'jenny', '56789', '0198726678', 'Jasin', 'jenny@user.com'),
('mandydy', 'mandy', '00000', '0178877667', 'Alor Gajah', 'mandy@user.com'),
('xue123', 'xuewing', '12345', '01677788909', 'Ayer Keroh', 'xue@user.com');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`admin_id`);

--
-- Indexes for table `booking`
--
ALTER TABLE `booking`
  ADD PRIMARY KEY (`booking_id`),
  ADD KEY `car_id` (`car_id`),
  ADD KEY `user_id` (`user_id`);

--
-- Indexes for table `car`
--
ALTER TABLE `car`
  ADD PRIMARY KEY (`car_id`);

--
-- Indexes for table `feedback`
--
ALTER TABLE `feedback`
  ADD PRIMARY KEY (`feedback_id`),
  ADD KEY `user_id` (`user_id`) USING BTREE,
  ADD KEY `booking_id` (`booking_id`);

--
-- Indexes for table `payment`
--
ALTER TABLE `payment`
  ADD PRIMARY KEY (`payment_id`),
  ADD KEY `user_id` (`user_id`),
  ADD KEY `booking_id` (`booking_id`);

--
-- Indexes for table `userdetail`
--
ALTER TABLE `userdetail`
  ADD PRIMARY KEY (`user_id`);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `booking`
--
ALTER TABLE `booking`
  ADD CONSTRAINT `booking_ibfk_1` FOREIGN KEY (`car_id`) REFERENCES `car` (`car_id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
