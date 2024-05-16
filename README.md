# TripTactics
Welcome to the TripTactics ! This application is your ultimate travel companion, designed to make trip planning enjoyable.

## About TripTactics
TripTactics is a travel planning application that helps users organize their trips with ease. From finding the best flights and accommodations to discovering local attractions and activities, TripTactics offers a comprehensive solution for all your travel needs.

## Features
• Integrated Experience: TripTactics can offer a seamless integration of flights, hotels, activities, and budget management in one platform.  
• Customization: Provide more personalized options such as disabling certain planning features.  
• Get Information quickly: TripTactics provides information about local attractions and activities and provides links for quicker engagement.  

## Getting Started
## Screenshots
<img src="https://github.com/OmarT-Y/TravelPlaner/assets/73003302/e2cc33d8-81e8-4eb2-9d3d-63cc8a9ace8e" width="400" height="400">
<img src="https://github.com/OmarT-Y/TravelPlaner/assets/73003302/be4906d0-ab2d-4f4e-bec6-11ecc6ad5c85" width="400" height="400">
<img src="https://github.com/OmarT-Y/TravelPlaner/assets/73003302/7c6eff63-f7ce-4caa-869e-873751df9293" width="400" height="400">
<img src="https://github.com/OmarT-Y/TravelPlaner/assets/73003302/a92cec94-5c93-4fc9-891b-7446b920ee89" width="400" height="400">

## Functional Requirements:
### 1-	The User should be able to specify :   
    1-Origin City  
    2-Destination City  
    3-Start Date  
    4-End Date  
    5-Number of Adult Travelers  
    6-Number of Child Travelers  
    7-Currency Selection  
    8-Maximum Price for Flights  
    9-Maximum Price for Hotels  
    10-Minimum Rating for Hotels  
    11-Number of Hotel Rooms  
### 2-	The user should be able to Omit Flights planning or Omit Hotel Planning from the search results   
### 3-	The User should be able to specify Maximum price for flights   
### 4-	The User should be able to specify :  
    1-Maximum price for hotels   
    2-Minimum rating for hotels   
    3-Number of rooms required   
### 5-	The User should be able to choose Extra amenities such as :   
    1-Swimming pool   
    2-SPA  
    3-Fitness Centre   
    4-parking  
    5-Mini Bar   
    6-Baby Sitting  
    7-…….  
### 6-	The  User can use between EUR ,USD and EGP currencies  
### 7-	Date Selection should be allowed for the one way trips and for the roundtrips   
### 8-	When  user disables Hotel planning  , The hotel options will not be responding   
### 9-	When user disable Flights planning , The Flight Options will not be responding   
### 10-Data should be got using Rest APIs    
## Non-Functional Requirements :
1-Usability :
  -	The interface should be intuitive and every Entry point should have a text label to explain its significance
  -	Training time of Users is very low 
  -	If The input has only two options Such as (Enabled , Disabled ) it should take the input from the user using checkboxes 
  -	If Some options are not allowed to be chosen so they should not be displayed so for example do not display rupees because we can only allow Egyptian pounds . US Dollars and Euros 
2-Performance:
  -	The application should process user inputs and provide recommendations quickly.
3-Maintainability :
  -	Code Modularity: The application code should be modular to facilitate easy updates and maintenance.
  -	Documentation: The system should be well-documented using Class Diagrams , Use case diagrams and Sequence diagrams 
4- Reliability : 
	-Based on Reliable QT Framework
5- Size : Size of the program is in order of few mega bytes
6- Security : The data of the Trip is processed locally
    
    
## User Stories and Acceptance Criteria: 

### User Story 1: 

As a user 

I want to search for flights between two cities on specific dates. 

So that I can plan my travel itinerary efficiently. 

Acceptance Criteria: 

The user can enter the origin and destination cities. 

The user can select the start and end dates. 

The system displays a list of available flights between the specified cities for    the specified dates. 

 

 

### User Story 2: 

As a user 

I want to search for hotels in a destination city with specific criteria. 

So that I can find suitable accommodation for my trip. 

Acceptance Criteria: 

The user can enter the destination city. 

The user can select the start and end dates. 

The system displays a list of available hotels in the specified city for the specified dates.	 

 

 

### User Story 3: 

As a user 

I want to input my travel start and end dates. 

So that I can find available flights and hotels for those dates. 

Acceptance Criteria: 

The user can select a start date from a calendar input. 

The user can select an end date from a calendar input. 

The system validates that the end date is not before the start date. 

 

 

 

 

 

### User Story 4: 

As a user 

I want to specify the number of adult and child travelers. 

So that I can get accurate flight and hotel options. 

Acceptance Criteria: 

The user can specify the number of adult travelers. 

The user can specify the number of child travelers. 

The system validates that the number of travelers is a non-negative integer. 

 

 

### User Story 5: 

As a user 

I want to set a maximum price for flights. 

So that I can stay within my budget. 

Acceptance Criteria: 

The user can enter a maximum price for flights. 

The system validates that the maximum price is a non-negative number. 

The system displays flights within the specified budget. 

 

 

### User Story 6: 

As a user 

I want to set a maximum price for hotels. 

So that I can find accommodation that fits my budget. 

Acceptance Criteria: 

The user can enter a maximum price for hotels. 

The system validates that the maximum price is a non-negative number. 

The system displays hotels within the specified budget. 

 

 

### User Story 7: 

As a user 

I want to filter hotels by minimum rating. 

So that I can choose high-quality accommodations. 

Acceptance Criteria: 

The user can specify a minimum rating for hotels. 

The system validates that the rating is between 0 and 5. 

The system displays hotels with ratings equal to or higher than the specified minimum rating. 

 

### User Story 8: 

As a user 

I want to select the number of hotel rooms needed. 

So that I can accommodate all travelers comfortably. 

Acceptance Criteria: 

The user can specify the number of hotel rooms needed. 

The system validates that the number of rooms is a non-negative integer. 

The system includes the number of rooms in the hotel search criteria. 

 

 

### User Story 9: 

As a user 

I want to disable the flight planning option. 

So that I can focus only on booking hotels. 

Acceptance Criteria: 

The user can check a box to disable flight planning. 

When the box is checked, the flight planning options are hidden or disabled. 

The system does not include flight options in the travel plan when flight planning is disabled. 

 

 

### User Story 10: 

As a user 

I want to disable the hotel planning option. 

So that I can focus only on booking flights. 

Acceptance Criteria: 

The user can check a box to disable hotel planning. 

When the box is checked, the hotel planning options are hidden or disabled. 

The system does not include hotel options in the travel plan when hotel planning is disabled. 

 

### User Story 11: 

As a user 

I want to choose extra amenities for my hotel stay. 

So that I can enhance my travel experience. 

Acceptance Criteria: 

The user can select extra amenities for the hotel stay from a predefined list. 

The system includes the selected amenities in the hotel search criteria. 

The system displays hotels that offer selected amenities. 

 

### User Story 12: 

As a user 

I want to select the currency for the price display. 

So that I can view costs in my preferred currency. 

Acceptance Criteria: 

The user can select a currency from a dropdown menu. 

The system displays prices in the selected currency. 

The system converts prices accurately based on current exchange rates. 

 

### User Story 13: 

As a user 

I want to be able to select the origin city using the abbreviation of the airport I want to use. 

So that I can precisely specify the airport I want to use. 

Acceptance Criteria: 

The user can search for a city by writing only the abbreviation of its airport. 

The program views the city and other suggestions in a drop-down menu. 

 

### User Story 14: 

As a user 

I want to be able to select the destination city using the abbreviation of the airport I want to use. 

So that I can precisely specify the airport I want to use. 

Acceptance Criteria: 

The user can search for a city by writing only the abbreviation of its airport. 

The program views the city and other suggestions in a drop-down menu. 

### User Story 15: 

As a user 

I want to be able to read the text labels and have smooth interactions with the buttons. 

So that I can enjoy easy experiences with the program. 

Acceptance Criteria: 

The fonts and the alignments should be appealing to the users. 

The buttons should be big enough to press on. 

The drop-down menus should be large enough to select from. 


 

### User Story 16: 

As a user 

I want to be able to view local attraction sites in the destination city. 

So that I can plan for visiting them. 

Acceptance Criteria: 

The user can navigate through different tabs and see what is suggested in the local attractions and activities tab. 

 

### User Story 17: 

As a user 

I want to be able to view local activities in the destination city in the time frame I am providing. 

So that I can attend these activities and put them on my time schedule. 

Acceptance Criteria: 

The user can navigate through different tabs and see what is suggested in the local attractions and activities tab. 
