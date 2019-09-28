<?php
/**
     * Get current user IP Address.
     * @return string
     */
    function get_ip_address() {
        if ( isset( $_SERVER['HTTP_X_REAL_IP'] ) ) {
            return $_SERVER['HTTP_X_REAL_IP'];
        } elseif ( isset( $_SERVER['HTTP_X_FORWARDED_FOR'] ) ) {
            // Proxy servers can send through this header like this: X-Forwarded-For: client1, proxy1, proxy2
            // Make sure we always only send through the first IP in the list which should always be the client IP.
            return (string) self::is_ip_address( trim( current( explode( ',', $_SERVER['HTTP_X_FORWARDED_FOR'] ) ) ) );
        } elseif ( isset( $_SERVER['REMOTE_ADDR'] ) ) {
            return $_SERVER['REMOTE_ADDR'];
        }
        return '';
    }

	echo get_ip_address();
?>
