enum StatusDouble
{
    GREATER,                                     /**< First double is greater than second */
    EQUALS,                                      /**< First double equals second */
    LESS                                         /**< First double is less than second */
};

/**
 * \brief Compares two doubles
 *
 * \param number1 - first number
 * \param number2 - second number
 *
 * \return status of comparing of two doubles
 */
StatusDouble compareDouble(double number1, double number2);
