Booking_Flight()
{
	
	char *sCity;
	int iCount;

	web_reg_find("SaveCount=CountWebTours",
		"Text=Web Tours",
		LAST);
	
	//This is a change for git.
	
	web_reg_save_param_ex(
		"ParamName=UserSession",
		"LB=name=\"userSession\" value=\"",
		"RB=\"/>",
		SEARCH_FILTERS,
		LAST);
	
	lr_start_transaction("WorkShop_BookingFlight_Launch_T01");

	web_url("index.htm", 
		"URL=http://127.0.0.1:1080/WebTours/index.htm", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t18.inf", 
		"Mode=HTML", 
		LAST);
	
	//

	iCount = atoi(lr_eval_string("{CountWebTours}"));

	//COuntwebtours(LR_Param) --> String (lr_eval_string) --> INT (atoi)
		
		
	
	if (iCount > 5) {
		lr_end_transaction("WorkShop_BookingFlight_Launch_T01", LR_PASS);
		lr_output_message("The count us correct");
	}
	
	else {
		
		lr_end_transaction("WorkShop_BookingFlight_Launch_T01", LR_FAIL);
		lr_error_message("The count is incorrect");
		lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_FAIL);
		//LR_EXIT_ITERATION_AND_CONTINUE
	}
	

	/* ************LOGIN**************** */

	web_reg_find("Text=Web Tours", 
		LAST);

	lr_think_time(17);
	
	lr_start_transaction("WorkShop_BookingFlight_Login_T02");
	
	lr_rendezvous("WorkShopTSys_Rendez_Login");

	web_submit_data("login.pl", 
		"Action=http://127.0.0.1:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=body", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?in=home", 
		"Snapshot=t19.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=userSession", "Value={UserSession}", ENDITEM, 
		"Name=username", "Value={Username}", ENDITEM, 
		"Name=password", "Value={Password}", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=login.x", "Value=0", ENDITEM, 
		"Name=login.y", "Value=0", ENDITEM, 
		LAST);
	
	lr_end_transaction("WorkShop_BookingFlight_Login_T02", LR_AUTO);

	/* **********CLICK FLIGHTS*********** */

	web_reg_find("Text=Web Tours", 
		LAST);

	lr_think_time(13);

lr_start_transaction("WorkShop_BookingFlight_ClickFlight_T03");

		web_reg_save_param_ex(
		"ParamName=Cities",
		"LB=<option value=\"",
		"RB=\">",
		"Ordinal=ALL",
		SEARCH_FILTERS,
		LAST);

			web_url("Search Flights Button", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t20.inf", 
		"Mode=HTML", 
		LAST);

	web_set_sockets_option("SSL_VERSION", "2&3");

	web_url("FormDateUpdate.class", 
		"URL=http://127.0.0.1:1080/WebTours/classes/FormDateUpdate.class", 
		"TargetFrame=", 
		"Resource=1", 
		"Referer=", 
		"Snapshot=t21.inf", 
		LAST);

	lr_end_transaction("WorkShop_BookingFlight_ClickFlight_T03", LR_AUTO);


	/* ************** SELECT CITY AND CONTINUE************ */

	web_reg_find("Text=Flight Selections", 
		LAST);

	lr_think_time(23);

	lr_start_transaction("WorkShop_BookingFlight_SelectCity_T04");
	
	sCity = lr_paramarr_random("Cities");
	
	lr_save_string(sCity,"lr_Departure_City");


		web_submit_data("reservations.pl", 
		"Action=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t22.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={lr_Departure_City}", ENDITEM, 
		"Name=departDate", "Value=07/27/2019", ENDITEM, 
		"Name=arrive", "Value=Paris", ENDITEM, 
		"Name=returnDate", "Value=07/28/2019", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatPref", "Value=None", ENDITEM, 
		"Name=seatType", "Value=Coach", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		"Name=findFlights.x", "Value=62", ENDITEM, 
		"Name=findFlights.y", "Value=15", ENDITEM, 
		LAST);

	lr_end_transaction("WorkShop_BookingFlight_SelectCity_T04", LR_AUTO);

	
	/* ***************SELECT DEPARTURE TIME********* */

	web_reg_find("Text=Flight Reservation", 
		LAST);

	lr_start_transaction("WorkShop_BookingFlight_SelectTime_T05");

		web_submit_data("reservations.pl_2", 
		"Action=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
		"Snapshot=t23.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=outboundFlight", "Value=041;312;07/27/2019", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=seatType", "Value=Coach", ENDITEM, 
		"Name=seatPref", "Value=None", ENDITEM, 
		"Name=reserveFlights.x", "Value=42", ENDITEM, 
		"Name=reserveFlights.y", "Value=7", ENDITEM, 
		LAST);


	lr_end_transaction("WorkShop_BookingFlight_SelectTime_T05", LR_AUTO);

	/* ****************INSERT PAYMENT DETAILS*********** */

	web_reg_find("Text=Reservation Made!", 
		LAST);

	lr_think_time(28);

	lr_start_transaction("WorkShop_BookingFlight_PaymentDetails_T06");

		web_submit_data("reservations.pl_3", 
		"Action=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
		"Snapshot=t24.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value=Jojo", ENDITEM, 
		"Name=lastName", "Value=Bean", ENDITEM, 
		"Name=address1", "Value=", ENDITEM, 
		"Name=address2", "Value=", ENDITEM, 
		"Name=pass1", "Value=Jojo Bean", ENDITEM, 
		"Name=creditCard", "Value=12354645456", ENDITEM, 
		"Name=expDate", "Value=", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatType", "Value=Coach", ENDITEM, 
		"Name=seatPref", "Value=None", ENDITEM, 
		"Name=outboundFlight", "Value=041;312;07/27/2019", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value=", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		"Name=buyFlights.x", "Value=63", ENDITEM, 
		"Name=buyFlights.y", "Value=4", ENDITEM, 
		LAST);

	lr_end_transaction("WorkShop_BookingFlight_PaymentDetails_T06", LR_AUTO);


	/* ************** SIGN OFF ************** */

	web_reg_find("Text=Web Tours", 
		LAST);

	lr_think_time(11);

	lr_start_transaction("WorkShop_BookingFlight_LogOFF_T07");
	
	lr_rendezvous("WorkSHopTSys_Rendez_LofOFF");

		web_url("SignOff Button", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t25.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("WorkShop_BookingFlight_LogOFF_T07", LR_AUTO);


	return 0;
}