// pages/set/set.js
Page({
    /**
     * 页面的初始数据
     */
    data: {
        canIUse: wx.canIUse('button.open-type'), //判断button下的open.type属性是在当前版本否支持
        isHide:false
    },
    //在page页面引入app，同时声明变量，获得所需要的全局变量
    /**
     * 生命周期函数--监听页面加载
     */
    onLoad: function (options) {
        wx.getSetting({     //获取用户的当前设置。返回值中只会出现小程序已经向用户请求过的权限。
            success: function(res)              //返回成功时
            {
              if(res.authSetting['scope.userInfo'])  //授权用户信息
              {
              wx.getUserInfo({              //获取用户的信息成功后并打印在控制台
                success:function(res){
                  console.log(res.userInfo.avatarUrl);
                }
              });
              }
            }
            
          })
    },
    
    bindGetUserInfo:function(e)     //当用户点击授权登录按钮触发 bindGetUserInfo函数
    {
      if(e.detail.userInfo)      //触发后返回到detail中，detail调用userInfo获取用户信息
      {
        wx.navigateTo({
          url: '../home/home',
        })
      }
      else{
          wx.showModal({           //如果用户选择拒绝,会提示用户是否返回去授权
            title: '提示',
            content: '您选择了拒绝您将无法进入小程序当中',
            showCancel:false,
            confirmText:'返回授权',
            success:function(res)   
            {
               if(res.confirm)
               {
                 console.log("点击了授权登录")
               }
            }
          });
      }
    },
    
    /**
     * 生命周期函数--监听页面初次渲染完成
     */
    onReady: function () {

    },

    /**
     * 生命周期函数--监听页面显示
     */
    onShow: function () {

    },

    /**
     * 生命周期函数--监听页面隐藏
     */
    onHide: function () {

    },

    /**
     * 生命周期函数--监听页面卸载
     */
    onUnload: function () {

    },

    /**
     * 页面相关事件处理函数--监听用户下拉动作
     */
    onPullDownRefresh: function () {

    },

    /**
     * 页面上拉触底事件的处理函数
     */
    onReachBottom: function () {

    },

    /**
     * 用户点击右上角分享
     */
    onShareAppMessage: function () {

    }
})