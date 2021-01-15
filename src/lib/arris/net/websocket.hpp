#pragma once
#include <vector>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <arris/net/constant.hpp>
#include <arris/net/net.hpp>
#include <arris/util/log_util.hpp>
#include <arris/util/json_util.hpp>

#include <arris/thread/wxthread.hpp>

#include <arris/wechat/wxmgr.hpp>
#include <arris/wechat/abnormalmsg.hpp>
#include <nlohmann/json.hpp>
using nlohmann::json;



using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using namespace arris::net;
using namespace arris::util;
using namespace arris::wechat;
using namespace arris::thread;


namespace arris {
namespace net {
    class wsserver :public inet{
        using server = websocketpp::server<websocketpp::config::asio>;
        using message_ptr = server::message_ptr;

    public:
        wsserver() {
            server_ = std::make_unique<server>();
            abnormal_msg_ = std::make_unique<abnormal_msg>();
            tinyjson_ = std::make_unique<tinyjson>();
            msg_mgr_ = std::make_unique<msg_mgr>();
            
            this->port_ = kPort;
            loop();//start loop
        }

        void port(unsigned int port) {
            this->port_ = port;
        }
        ~wsserver() {
            stop();
        }
        void start() {
            try {
                // Initialize ASIO
                server_->init_asio();
                server_->set_reuse_addr(true);

                // Register our message handler
                //server_->set_socket_init_handler(std::bind(&wsserver::init_send_msg_loop,this));
                server_->set_open_handler(std::bind(&wsserver::on_open,this,::_1));
                server_->set_message_handler(std::bind(&wsserver::on_message, this, ::_1, ::_2));
                server_->set_http_handler(std::bind(&wsserver::on_http, this, ::_1));
                server_->set_fail_handler(std::bind(&wsserver::on_fail, this, ::_1));
                server_->set_close_handler(std::bind(&wsserver::on_close, this, ::_1));

                server_->set_validate_handler(std::bind(&wsserver::validate, this));

                // Listen on port 
                server_->listen(this->port_);

                // Start the server accept loop
                server_->start_accept();

                //loop();
                // Start the ASIO io_service run loop
                server_->run();

            }
            catch (websocketpp::exception const& e) {
                __OutputDebugString(TEXT("websocketpp exception:%s\n"),e.what());
            }
            catch (const std::exception& e) {
                __OutputDebugString(TEXT("std exception:%s\n"), e.what());
            }
            catch (...) {
                __OutputDebugString(TEXT("other exception!please review code!\n"));
            }
        }
        void stop() {
            server_->stop();
        }

    protected:
        void loop()
        {
            thread_pool.enqueue(std::bind(&wsserver::send_msg_to_client, this));
        }
        void send_msg_to_client() {
            __OutputDebugString(TEXT("send msg to client begin!"));
            while (1) {
                //__OutputDebugString(TEXT("queue size:%d\n"), kMsgQueue.size());
                //__OutputDebugString(TEXT("hdl_ size:%d\n"), hdl_.size());
                if (kMsgQueue.size() > 0) {
                    std::string queue_msg = kMsgQueue.front();
                    for (size_t i = 0; i < hdl_.size();i++) {
                        websocketpp::connection_hdl hdl = hdl_[i];
                        this->server_->send(hdl, queue_msg, websocketpp::frame::opcode::text);
                    }
                    kMsgQueue.pop();
                }
                
            }
        }
        /*void send_to_client(websocketpp::connection_hdl hdl, message_ptr msg) {
            __OutputDebugString(TEXT("queue size:%d\n"), kMsgQueue.size());
            if (kMsgQueue.size()>0) {
                std::string queue_msg = kMsgQueue.front();
                this->server_->send(hdl,queue_msg, msg->get_opcode());
                kMsgQueue.pop();
            }
        }*/
        void handle_msg(const std::string& msg) {

           bool js_json_type= tinyjson_->is_json(msg);
           if (js_json_type ==true) {
               int type = tinyjson_->get_type(msg);
               wx_msg st_msg = tinyjson_->get_st(msg);
               __OutputDebugString(TEXT("type is :%d\n"),type);
               //msg_mgr_->
               msg_mgr_->run(type,st_msg);
           }
           else {
               std::string content = "its not json type!";
               abnormal_msg_->handled_msg(content);
           }
           
        }
        bool validate() {
            //sleep(6);
            return true;
        }

        void on_message(websocketpp::connection_hdl hdl, message_ptr msg) {
            //__OutputDebugString(TEXT("hello world"));
            try {
                handle_msg(msg->get_payload());
                //send_to_client(hdl,msg);
            }
            catch (websocketpp::exception const& e) {
                __OutputDebugString(TEXT("websocket send exception:%s\n"), e.what());
            }
        }
        void on_fail(websocketpp::connection_hdl hdl) 
        {
            server::connection_ptr con = this->server_->get_con_from_hdl(hdl);
            __OutputDebugString(TEXT("websocket send exception:%s\n"), con->get_ec().message());

        }
        void on_close(websocketpp::connection_hdl hdl) {
            
            //free hdl
            hdl_.erase(std::remove_if(std::begin(hdl_), std::end(hdl_),
                [&](const websocketpp::connection_hdl& a) {
                if (a.lock() == hdl.lock()) return true;
                return false;
            }));
            __OutputDebugString(TEXT("websocket close handler!\n"));
        }
        void on_http(websocketpp::connection_hdl hdl) {
            server::connection_ptr con = this->server_->get_con_from_hdl(hdl);

            std::string res = con->get_request_body();

            std::stringstream ss;

            con->set_body(ss.str());
            con->set_status(websocketpp::http::status_code::ok);
        }
        void on_open(websocketpp::connection_hdl hdl) {
            //__OutputDebugString(TEXT("hdl_"));
            hdl_.push_back(hdl);
        }
    private:
        std::vector<websocketpp::connection_hdl> hdl_;
        std::unique_ptr<server> server_;
        std::unique_ptr<msg_mgr> msg_mgr_;
        std::unique_ptr<abnormal_msg> abnormal_msg_;
        std::unique_ptr<tinyjson> tinyjson_;
        unsigned int port_;


    };// class wsserver        
}//namespace net
}//namespace arris