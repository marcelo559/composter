--
-- Table structure for table `table_name`
--

CREATE TABLE `table_name` (
  `id_registro` int(11) NOT NULL COMMENT 'Save the ID of the records',
  `id_sensor` int(4) DEFAULT NULL COMMENT 'All sensor must have an INT ID',
  `avatar` varchar(22) COLLATE latin1_general_ci DEFAULT NULL COMMENT 'Sensor Avatar (DHT11Box1/DHT11Box2)',
  `measurement_type` int(11) DEFAULT NULL COMMENT '0=Temp / 1=Hum',
  `sensor_value` float DEFAULT NULL,
  `unit` int(2) DEFAULT NULL COMMENT '0=Celsius/1=Percent',
  `date_time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci COMMENT='';
