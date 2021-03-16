#include <bits/stdc++.h>
using namespace std;


class GitEngine{
    private:
    
    string TextOutputExecute(const char* cmd) {
        array<char, 1024> buffer;
        string result;
        unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        if (!pipe) {
            throw runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        return result;
    }

    public:

    void InitalizeGitRepository(string local_repo_path, string commit_message, string files_to_add, string remote_url){
        if(remote_url.size()==0){
            cout<<"> Remote Please specify remote URL"<<endl;
            return;
        }
        if(local_repo_path.size()!=0){
            string cmd = "cd ";
            cmd+=local_repo_path;
            system(&cmd[0]);
        }
        if(commit_message==""){
            commit_message = "\"first commit\"";
        }else{
            commit_message = "\"" + commit_message+ "\"";
        }
        if(files_to_add==""){
            files_to_add = ".";
        }

        string process[] = {"git init",  "git add "+files_to_add,  "git commit -m "+commit_message,  "git remote add origin "+remote_url,  "git remote -v",  "git push origin master"};
        for(int i =0;i<6;i++){
            system(&process[i][0]);
        }
    }

    void ForcePush(){
        system("git push origin master --force");
    }

    void CurrentRemoteRepository(){
        system("git remote -v");
    }

    void SyncronizeAllToMasterRemote(string commit_message){
        if(commit_message.size()==0){
            cout<<"Commit message cannot be empty"<<endl;
        }else{
            system("git add .");
            string cmd="git commit -m";
            cmd += "\"" + commit_message+ "\"";
            system(&cmd[0]);
            system("git push origin master");
        }
    }

};



int main(int argc, char const *argv[]){
   GitEngine g;
   
   return 0;
}

