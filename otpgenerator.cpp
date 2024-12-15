#include<iostream>
#include<random>
#include<fstream>
#include<cstdlib>
#include<chrono>
#include<thread>

using namespace std;
using namespace chrono;

int randomnumber(){
    random_device num;
    
    mt19937 gen(num());

    uniform_int_distribution<>distr(1000,9999);

    return distr(gen);
}
void sendotp(int otp , string email){
    ofstream emailfile("otp_email.txt");
    emailfile<<"your otp is : "<<otp<<"valid for 5 minutes.\n";
    emailfile.close();
    string command = "sendemail:"+email+"<otp_email.txt";
    system(command.c_str());
}

int main(){
    string useremail;
    cout<<"enter email:";
    cin>>useremail;
    
    int otp = randomnumber();
    sendotp(otp,useremail);
    cout<<"otp has been sent.\n";
    auto otpgeneratortime=steady_clock::now();
    int otpvalidilityseconds=300;

    int enetrotp;
    cin>>enetrotp;
    auto currenttime=steady_clock::now();
    auto timeElapsed=duration_cast<seconds>(currenttime-otpgeneratortime).count();
    if( timeElapsed > otpvalidilityseconds ){
        cout<<"otp expired.request again"<<endl;
    }else if(enetrotp==otp){
        cout<<"entered otp is correct.Access granted"<<endl;
    }else{
        cout<<"incorrect otp.Try again"<<endl;
    }
    return 0;
}