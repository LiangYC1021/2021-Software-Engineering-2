// pages/help/help.js
Page({

    /**
     * 页面的初始数据
     */
    data: {
        modalHidden:true,//是否隐藏对话框
    },
    showWindows1: function() {
        wx.showModal({
          title: '提示',
          content: '每位玩家需要设置自己在游戏中的ID、头像，用以区分玩家。\n玩家信息设置后选择创建房间或者加入房间以进行多人游戏。\n若选择创建房间，房主需要设置每个奖项所对应的奖品和数量。\n游戏中，每位玩家在自己的轮次中投出六个🎲，按照博饼规则所对应的结果进行奖品的分配或其他娱乐操作哦。',
          success (res) {
            if (res.confirm) {
              console.log('用户点击确定')
            } else if (res.cancel) {
              console.log('用户点击取消')
            }
          }
        })
        },
    showWindows2: function() {
            this.setData({
              modalHidden: false
            })
          },
        
          /**
           * 点击取消
           */
          modalCandel: function() {
            // do something
            this.setData({
              modalHidden: true
            })
          },
        
          /**
           *  点击确认
           */
          modalConfirm: function() {
            // do something
            this.setData({
              modalHidden: true
            })
          }
        
})